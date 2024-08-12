#include <stdio.h>

int main() {
    char a;
    short b;
    int c;
    float d;
    int x, y, z;
    x = 30;
    int i = 50;

    // 변수들을 사용하지 않는다면 컴파일러가 최적화에 의해 경고를 출력할 수 있습니다.
    // 이를 방지하기 위해 사용되는 변수에 값을 출력하는 등의 작업을 추가할 수 있습니다.
    printf("x: %d, i: %d\n", x, i);

    return 0;
}