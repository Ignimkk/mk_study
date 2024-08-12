import cv2
import numpy as np
import torch

# Open the video capture
cap = cv2.VideoCapture('drive.webmqqq')
cap.set(cv2.CAP_PROP_FRAME_WIDTH, 640)
cap.set(cv2.CAP_PROP_FRAME_HEIGHT, 480)

# Load a different, possibly better-suited model
road_segmentation_model = torch.hub.load('pytorch/vision:v0.10.0', 'deeplabv3_resnet101', pretrained=True)
road_segmentation_model.eval()

def preprocess(frame):
    # Convert to a different color space if necessary, e.g., HSV or LAB
    frame_hsv = cv2.cvtColor(frame, cv2.COLOR_BGR2HSV)
    return frame_hsv

def segment_road(frame):
    # Assume input frame is already in RGB
    input_tensor = torch.from_numpy(frame).permute(2, 0, 1).unsqueeze(0).float() / 255.0
    with torch.no_grad():
        output = road_segmentation_model(input_tensor)['out'][0]
    return output.argmax(0).byte().cpu().numpy()

while True:
    ret, frame = cap.read()
    if not ret:
        break
    
    frame = cv2.resize(frame, (640, 480), interpolation=cv2.INTER_AREA)
    preprocessed_frame = preprocess(frame)  # Apply preprocessing
    road_mask = segment_road(preprocessed_frame)

    # Visualize the road mask to check detection
    road_visualization = (road_mask * 255).astype(np.uint8)
    cv2.imshow("Road Mask", road_visualization)

    if cv2.waitKey(1) & 0xFF == ord('q'):
        break

cap.release()
cv2.destroyAllWindows()
