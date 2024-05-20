{
    "type": "MySQLNotebook",
    "version": "1.0",
    "caption": "DB Notebook",
    "content": "\\about\nuse amrbase;\ndesc oil_price;\nSELECT * from sandwich;\nSELECT UCASE(Cafe), LCASE(Menu) from sandwich;\nSELECT Rank_id, LENGTH(Menu), Menu, MID(Menu, -1) from sandwich where RANK_id = 10;\nSELECT length(Menu) from sandwich ; \nSELECT AVG(length(Menu)) from sandwich ;\nSELECT * from oil_price;\nSELECT ROUND(가격, -2) from oil_price;\nselect format(가격, 0), 가격 from oil_price where round(가격, -2) >= 2000;\n\n",
    "options": {
        "tabSize": 4,
        "insertSpaces": true,
        "indentSize": 4,
        "defaultEOL": "LF",
        "trimAutoWhitespace": true
    },
    "viewState": {
        "cursorState": [
            {
                "inSelectionMode": false,
                "selectionStart": {
                    "lineNumber": 11,
                    "column": 69
                },
                "position": {
                    "lineNumber": 11,
                    "column": 69
                }
            }
        ],
        "viewState": {
            "scrollLeft": 0,
            "firstPosition": {
                "lineNumber": 10,
                "column": 1
            },
            "firstPositionDeltaTop": 268
        },
        "contributionsState": {
            "editor.contrib.folding": {},
            "editor.contrib.wordHighlighter": false
        }
    },
    "contexts": [
        {
            "state": {
                "start": 1,
                "end": 1,
                "language": "mysql",
                "result": {
                    "type": "text",
                    "text": [
                        {
                            "type": 2,
                            "content": "Welcome to the MySQL Shell - DB Notebook.\n\nPress Ctrl+Enter to execute the code block.\n\nExecute \\sql to switch to SQL, \\js to JavaScript and \\ts to TypeScript mode.\nExecute \\help or \\? for help;",
                            "language": "ansi"
                        }
                    ]
                },
                "currentHeight": 151.984375,
                "statements": [
                    {
                        "delimiter": ";",
                        "span": {
                            "start": 0,
                            "length": 6
                        },
                        "contentStart": 0,
                        "state": 0
                    }
                ]
            },
            "data": []
        },
        {
            "state": {
                "start": 2,
                "end": 2,
                "language": "mysql",
                "result": {
                    "type": "text",
                    "text": [
                        {
                            "type": 4,
                            "index": 0,
                            "resultId": "77c39c5d-ad90-4000-f04b-75a1ba07245a",
                            "content": "OK, 0 records retrieved in 4.306ms"
                        }
                    ]
                },
                "currentHeight": 28,
                "statements": [
                    {
                        "delimiter": ";",
                        "span": {
                            "start": 0,
                            "length": 12
                        },
                        "contentStart": 0,
                        "state": 0
                    }
                ]
            },
            "data": []
        },
        {
            "state": {
                "start": 3,
                "end": 3,
                "language": "mysql",
                "result": {
                    "type": "resultIds",
                    "list": [
                        "5987b654-7995-49e8-beb4-2ce21e506dc0"
                    ]
                },
                "currentHeight": 36,
                "statements": [
                    {
                        "delimiter": ";",
                        "span": {
                            "start": 0,
                            "length": 15
                        },
                        "contentStart": 1,
                        "state": 0
                    }
                ]
            },
            "data": [
                {
                    "tabId": "e706df21-6856-490e-f719-1d86ecb4e120",
                    "resultId": "5987b654-7995-49e8-beb4-2ce21e506dc0",
                    "rows": [
                        {
                            "0": "ID",
                            "1": "int",
                            "2": "YES",
                            "3": "",
                            "4": null,
                            "5": ""
                        },
                        {
                            "0": "상호",
                            "1": "varchar(16)",
                            "2": "YES",
                            "3": "",
                            "4": null,
                            "5": ""
                        },
                        {
                            "0": "주소",
                            "1": "varchar(255)",
                            "2": "YES",
                            "3": "",
                            "4": null,
                            "5": ""
                        },
                        {
                            "0": "가격",
                            "1": "int",
                            "2": "YES",
                            "3": "",
                            "4": null,
                            "5": ""
                        },
                        {
                            "0": "셀프",
                            "1": "char(1)",
                            "2": "YES",
                            "3": "",
                            "4": null,
                            "5": ""
                        },
                        {
                            "0": "상표",
                            "1": "varchar(16)",
                            "2": "YES",
                            "3": "",
                            "4": null,
                            "5": ""
                        },
                        {
                            "0": "구",
                            "1": "varchar(8)",
                            "2": "YES",
                            "3": "",
                            "4": null,
                            "5": ""
                        }
                    ],
                    "columns": [
                        {
                            "title": "Field",
                            "field": "0",
                            "dataType": {
                                "type": 17
                            }
                        },
                        {
                            "title": "Type",
                            "field": "1",
                            "dataType": {
                                "type": 17
                            }
                        },
                        {
                            "title": "Null",
                            "field": "2",
                            "dataType": {
                                "type": 17
                            }
                        },
                        {
                            "title": "Key",
                            "field": "3",
                            "dataType": {
                                "type": 46
                            }
                        },
                        {
                            "title": "Default",
                            "field": "4",
                            "dataType": {
                                "type": 17
                            }
                        },
                        {
                            "title": "Extra",
                            "field": "5",
                            "dataType": {
                                "type": 17
                            }
                        }
                    ],
                    "executionInfo": {
                        "text": "OK, 7 records retrieved in 4.496ms"
                    },
                    "totalRowCount": 7,
                    "hasMoreRows": false,
                    "currentPage": 0,
                    "index": 0,
                    "sql": "desc oil_price"
                }
            ]
        },
        {
            "state": {
                "start": 4,
                "end": 4,
                "language": "mysql",
                "result": {
                    "type": "resultIds",
                    "list": [
                        "0bbd69fa-6655-4afe-fd16-42a358534bd0"
                    ]
                },
                "currentHeight": 36,
                "statements": [
                    {
                        "delimiter": ";",
                        "span": {
                            "start": 0,
                            "length": 23
                        },
                        "contentStart": 0,
                        "state": 0
                    }
                ]
            },
            "data": [
                {
                    "tabId": "e706df21-6856-490e-f719-1d86ecb4e120",
                    "resultId": "0bbd69fa-6655-4afe-fd16-42a358534bd0",
                    "rows": [
                        {
                            "0": 1,
                            "1": "Old Oak Tap",
                            "2": "BLT",
                            "3": 10,
                            "4": "2109 W. Chicago Ave"
                        },
                        {
                            "0": 2,
                            "1": "Au Cheval",
                            "2": "Fried Bologna",
                            "3": 9,
                            "4": "800 W. Randolph St"
                        },
                        {
                            "0": 3,
                            "1": "Xoco",
                            "2": "Woodland Mushroom",
                            "3": 10,
                            "4": " 445 N. Clark St"
                        },
                        {
                            "0": 4,
                            "1": "Al’s Deli",
                            "2": "Roast Beef",
                            "3": 9,
                            "4": " 914 Noyes St"
                        },
                        {
                            "0": 5,
                            "1": "Publican Quality Meats",
                            "2": "PB&L",
                            "3": 10,
                            "4": "825 W. Fulton Mkt"
                        },
                        {
                            "0": 6,
                            "1": "Hendrickx Belgian Bread Crafter",
                            "2": "Belgian Chicken Curry Salad",
                            "3": 7,
                            "4": " 100 E. Walton St"
                        },
                        {
                            "0": 7,
                            "1": "Acadia",
                            "2": "Lobster Roll",
                            "3": 16,
                            "4": "1639 S. Wabash Ave"
                        },
                        {
                            "0": 8,
                            "1": "Birchwood Kitchen",
                            "2": "Smoked Salmon Salad",
                            "3": 10,
                            "4": "2211 W. North Ave"
                        },
                        {
                            "0": 9,
                            "1": "Cemitas Puebla",
                            "2": "Atomica Cemitas",
                            "3": 9,
                            "4": "3619 W. North Ave"
                        },
                        {
                            "0": 10,
                            "1": "Nana",
                            "2": "Grilled Laughing Bird Shrimp and",
                            "3": 17,
                            "4": "3267 S. Halsted St"
                        },
                        {
                            "0": 11,
                            "1": "Lula Cafe",
                            "2": "Ham and Raclette Panino",
                            "3": 11,
                            "4": "2537 N. Kedzie Blvd"
                        },
                        {
                            "0": 12,
                            "1": "Ricobene’s",
                            "2": "Breaded Steak",
                            "3": 5,
                            "4": " Multiple location"
                        },
                        {
                            "0": 13,
                            "1": "Frog n Snail",
                            "2": "The Hawkeye",
                            "3": 14,
                            "4": "3124 N. Broadwa"
                        },
                        {
                            "0": 14,
                            "1": "Crosby’s Kitchen",
                            "2": "Chicken Dip",
                            "3": 10,
                            "4": "3455 N. Southport Ave"
                        },
                        {
                            "0": 15,
                            "1": "Longman & Eagle",
                            "2": "Wild Boar Sloppy Joe",
                            "3": 13,
                            "4": "2657 N. Kedzie Ave"
                        },
                        {
                            "0": 16,
                            "1": "Bari",
                            "2": "Meatball Sub",
                            "3": 5,
                            "4": " 1120 W. Grand Ave"
                        },
                        {
                            "0": 17,
                            "1": "Manny’s",
                            "2": "Corned Beef",
                            "3": 12,
                            "4": " 1141 S. Jefferson St"
                        },
                        {
                            "0": 18,
                            "1": "Eggy’s",
                            "2": "Turkey Club",
                            "3": 12,
                            "4": " 333 E. Benton Pl"
                        },
                        {
                            "0": 19,
                            "1": "Old Jerusalem",
                            "2": "Falafel",
                            "3": 6,
                            "4": " 1411 N. Wells St"
                        },
                        {
                            "0": 20,
                            "1": "Mindy’s HotChocolate",
                            "2": "Crab Cake",
                            "3": 15,
                            "4": "1747 N. Damen Ave"
                        },
                        {
                            "0": 21,
                            "1": "Olga’s Delicatessen",
                            "2": "Chicken Schnitzel",
                            "3": 5,
                            "4": "3209 W. Irving Park Rd"
                        },
                        {
                            "0": 22,
                            "1": "Dawali Mediterranean Kitchen",
                            "2": "Shawarma",
                            "3": 6,
                            "4": "Multiple location"
                        },
                        {
                            "0": 23,
                            "1": "Big Jones",
                            "2": "Toasted Pimiento Cheese",
                            "3": 8,
                            "4": "5347 N. Clark St"
                        },
                        {
                            "0": 24,
                            "1": "La Pane",
                            "2": "Vegetarian Panino",
                            "3": 6,
                            "4": " 2954 W. Irving Park Rd"
                        },
                        {
                            "0": 25,
                            "1": "Pastoral",
                            "2": "Cali Chèvre",
                            "3": 8,
                            "4": " Multiple location"
                        },
                        {
                            "0": 26,
                            "1": "Max’s Deli",
                            "2": "Pastrami",
                            "3": 12,
                            "4": " 191 Skokie Valley Rd"
                        },
                        {
                            "0": 27,
                            "1": "Lucky’s Sandwich Co.",
                            "2": "The Fredo",
                            "3": 8,
                            "4": " Multiple location"
                        },
                        {
                            "0": 28,
                            "1": "City Provisions",
                            "2": "Smoked Ham",
                            "3": 13,
                            "4": " 1818 W. Wilson Ave"
                        },
                        {
                            "0": 29,
                            "1": "Papa’s Cache Sabroso",
                            "2": "Jibarito",
                            "3": 7,
                            "4": "2517 W. Division St"
                        },
                        {
                            "0": 30,
                            "1": "Bavette’s Bar & Boeuf",
                            "2": "Shaved Prime Rib",
                            "3": 21,
                            "4": "218 W. Kinzie St"
                        },
                        {
                            "0": 31,
                            "1": "Hannah’s Bretzel",
                            "2": "Serrano Ham and Manchego Cheese",
                            "3": 10,
                            "4": " Multiple location"
                        },
                        {
                            "0": 32,
                            "1": "La Fournette",
                            "2": "Tuna Salad",
                            "3": 10,
                            "4": " 1547 N. Wells St"
                        },
                        {
                            "0": 33,
                            "1": "Paramount Room",
                            "2": "Paramount Reuben",
                            "3": 13,
                            "4": "415 N. Milwaukee Ave"
                        },
                        {
                            "0": 34,
                            "1": "Melt Sandwich Shoppe",
                            "2": "The Istanbul",
                            "3": 8,
                            "4": " 1840 N. Damen Ave"
                        },
                        {
                            "0": 35,
                            "1": "Floriole Cafe & Bakery",
                            "2": "B.A.D.",
                            "3": 9,
                            "4": "1220 W. Webster Ave"
                        },
                        {
                            "0": 36,
                            "1": "First Slice Pie Café",
                            "2": "Duck Confit and Mozzarella",
                            "3": 9,
                            "4": "5357 N. Ashland Ave"
                        },
                        {
                            "0": 37,
                            "1": "Troquet",
                            "2": "Croque Monsieur",
                            "3": 8,
                            "4": "1834 W. Montrose Ave"
                        },
                        {
                            "0": 38,
                            "1": "Grahamwich",
                            "2": "Green Garbanzo",
                            "3": 8,
                            "4": "615 N. State St"
                        },
                        {
                            "0": 39,
                            "1": "Saigon Sisters",
                            "2": "The Hen House",
                            "3": 7,
                            "4": "Multiple location"
                        },
                        {
                            "0": 40,
                            "1": "Rosalia’s Deli",
                            "2": "Tuscan Chicken",
                            "3": 6,
                            "4": "241 N. York Rd"
                        },
                        {
                            "0": 41,
                            "1": "Z&H MarketCafe",
                            "2": "The Marty ",
                            "3": 7,
                            "4": " 1323 E. 57th St"
                        },
                        {
                            "0": 42,
                            "1": "Market House on the Square",
                            "2": "Whitefish",
                            "3": 11,
                            "4": "655 Forest Ave"
                        },
                        {
                            "0": 43,
                            "1": "Elaine’s Coffee Call",
                            "2": "Oat Bread, Pecan Butter, and Fru",
                            "3": 6,
                            "4": "Hotel Lincol"
                        },
                        {
                            "0": 44,
                            "1": "Marion Street Cheese Market",
                            "2": "Cauliflower Melt",
                            "3": 9,
                            "4": "100 S. Marion St"
                        },
                        {
                            "0": 45,
                            "1": "Cafecito",
                            "2": "Cubana",
                            "3": 5,
                            "4": " 26 E. Congress Pkwy"
                        },
                        {
                            "0": 46,
                            "1": "Chickpea",
                            "2": "Kufta",
                            "3": 8,
                            "4": "2018 W. Chicago Ave"
                        },
                        {
                            "0": 47,
                            "1": "The Goddess and Grocer",
                            "2": "Debbie’s Egg Salad",
                            "3": 7,
                            "4": " 25 E. Delaware Pl"
                        },
                        {
                            "0": 48,
                            "1": "Zenwich",
                            "2": "Beef Curry",
                            "3": 8,
                            "4": " 416 N. York St"
                        },
                        {
                            "0": 49,
                            "1": "Toni Patisserie",
                            "2": "Le Végétarien",
                            "3": 9,
                            "4": " 65 E. Washington St"
                        },
                        {
                            "0": 50,
                            "1": "Phoebe’s Bakery",
                            "2": "The Gatsby",
                            "3": 7,
                            "4": " 3351 N. Broadwa"
                        }
                    ],
                    "columns": [
                        {
                            "title": "Rank_id",
                            "field": "0",
                            "dataType": {
                                "type": 4
                            }
                        },
                        {
                            "title": "Cafe",
                            "field": "1",
                            "dataType": {
                                "type": 17
                            }
                        },
                        {
                            "title": "Menu",
                            "field": "2",
                            "dataType": {
                                "type": 17
                            }
                        },
                        {
                            "title": "price",
                            "field": "3",
                            "dataType": {
                                "type": 4
                            }
                        },
                        {
                            "title": "Address",
                            "field": "4",
                            "dataType": {
                                "type": 17
                            }
                        }
                    ],
                    "executionInfo": {
                        "text": "OK, 50 records retrieved in 3.883ms"
                    },
                    "totalRowCount": 50,
                    "hasMoreRows": false,
                    "currentPage": 0,
                    "index": 0,
                    "sql": "SELECT * from sandwich"
                }
            ]
        },
        {
            "state": {
                "start": 5,
                "end": 5,
                "language": "mysql",
                "result": {
                    "type": "resultIds",
                    "list": [
                        "426a82f4-ca53-4f9e-9a4a-fc449881937d"
                    ]
                },
                "currentHeight": 36,
                "statements": [
                    {
                        "delimiter": ";",
                        "span": {
                            "start": 0,
                            "length": 46
                        },
                        "contentStart": 0,
                        "state": 0
                    }
                ]
            },
            "data": [
                {
                    "tabId": "e706df21-6856-490e-f719-1d86ecb4e120",
                    "resultId": "426a82f4-ca53-4f9e-9a4a-fc449881937d",
                    "rows": [
                        {
                            "0": "OLD OAK TAP",
                            "1": "blt"
                        },
                        {
                            "0": "AU CHEVAL",
                            "1": "fried bologna"
                        },
                        {
                            "0": "XOCO",
                            "1": "woodland mushroom"
                        },
                        {
                            "0": "AL’S DELI",
                            "1": "roast beef"
                        },
                        {
                            "0": "PUBLICAN QUALITY MEATS",
                            "1": "pb&l"
                        },
                        {
                            "0": "HENDRICKX BELGIAN BREAD CRAFTER",
                            "1": "belgian chicken curry salad"
                        },
                        {
                            "0": "ACADIA",
                            "1": "lobster roll"
                        },
                        {
                            "0": "BIRCHWOOD KITCHEN",
                            "1": "smoked salmon salad"
                        },
                        {
                            "0": "CEMITAS PUEBLA",
                            "1": "atomica cemitas"
                        },
                        {
                            "0": "NANA",
                            "1": "grilled laughing bird shrimp and"
                        },
                        {
                            "0": "LULA CAFE",
                            "1": "ham and raclette panino"
                        },
                        {
                            "0": "RICOBENE’S",
                            "1": "breaded steak"
                        },
                        {
                            "0": "FROG N SNAIL",
                            "1": "the hawkeye"
                        },
                        {
                            "0": "CROSBY’S KITCHEN",
                            "1": "chicken dip"
                        },
                        {
                            "0": "LONGMAN & EAGLE",
                            "1": "wild boar sloppy joe"
                        },
                        {
                            "0": "BARI",
                            "1": "meatball sub"
                        },
                        {
                            "0": "MANNY’S",
                            "1": "corned beef"
                        },
                        {
                            "0": "EGGY’S",
                            "1": "turkey club"
                        },
                        {
                            "0": "OLD JERUSALEM",
                            "1": "falafel"
                        },
                        {
                            "0": "MINDY’S HOTCHOCOLATE",
                            "1": "crab cake"
                        },
                        {
                            "0": "OLGA’S DELICATESSEN",
                            "1": "chicken schnitzel"
                        },
                        {
                            "0": "DAWALI MEDITERRANEAN KITCHEN",
                            "1": "shawarma"
                        },
                        {
                            "0": "BIG JONES",
                            "1": "toasted pimiento cheese"
                        },
                        {
                            "0": "LA PANE",
                            "1": "vegetarian panino"
                        },
                        {
                            "0": "PASTORAL",
                            "1": "cali chèvre"
                        },
                        {
                            "0": "MAX’S DELI",
                            "1": "pastrami"
                        },
                        {
                            "0": "LUCKY’S SANDWICH CO.",
                            "1": "the fredo"
                        },
                        {
                            "0": "CITY PROVISIONS",
                            "1": "smoked ham"
                        },
                        {
                            "0": "PAPA’S CACHE SABROSO",
                            "1": "jibarito"
                        },
                        {
                            "0": "BAVETTE’S BAR & BOEUF",
                            "1": "shaved prime rib"
                        },
                        {
                            "0": "HANNAH’S BRETZEL",
                            "1": "serrano ham and manchego cheese"
                        },
                        {
                            "0": "LA FOURNETTE",
                            "1": "tuna salad"
                        },
                        {
                            "0": "PARAMOUNT ROOM",
                            "1": "paramount reuben"
                        },
                        {
                            "0": "MELT SANDWICH SHOPPE",
                            "1": "the istanbul"
                        },
                        {
                            "0": "FLORIOLE CAFE & BAKERY",
                            "1": "b.a.d."
                        },
                        {
                            "0": "FIRST SLICE PIE CAFÉ",
                            "1": "duck confit and mozzarella"
                        },
                        {
                            "0": "TROQUET",
                            "1": "croque monsieur"
                        },
                        {
                            "0": "GRAHAMWICH",
                            "1": "green garbanzo"
                        },
                        {
                            "0": "SAIGON SISTERS",
                            "1": "the hen house"
                        },
                        {
                            "0": "ROSALIA’S DELI",
                            "1": "tuscan chicken"
                        },
                        {
                            "0": "Z&H MARKETCAFE",
                            "1": "the marty "
                        },
                        {
                            "0": "MARKET HOUSE ON THE SQUARE",
                            "1": "whitefish"
                        },
                        {
                            "0": "ELAINE’S COFFEE CALL",
                            "1": "oat bread, pecan butter, and fru"
                        },
                        {
                            "0": "MARION STREET CHEESE MARKET",
                            "1": "cauliflower melt"
                        },
                        {
                            "0": "CAFECITO",
                            "1": "cubana"
                        },
                        {
                            "0": "CHICKPEA",
                            "1": "kufta"
                        },
                        {
                            "0": "THE GODDESS AND GROCER",
                            "1": "debbie’s egg salad"
                        },
                        {
                            "0": "ZENWICH",
                            "1": "beef curry"
                        },
                        {
                            "0": "TONI PATISSERIE",
                            "1": "le végétarien"
                        },
                        {
                            "0": "PHOEBE’S BAKERY",
                            "1": "the gatsby"
                        }
                    ],
                    "columns": [
                        {
                            "title": "UCASE(Cafe)",
                            "field": "0",
                            "dataType": {
                                "type": 17
                            }
                        },
                        {
                            "title": "LCASE(Menu)",
                            "field": "1",
                            "dataType": {
                                "type": 17
                            }
                        }
                    ],
                    "executionInfo": {
                        "text": "OK, 50 records retrieved in 4.105ms"
                    },
                    "totalRowCount": 50,
                    "hasMoreRows": false,
                    "currentPage": 0,
                    "index": 0,
                    "sql": "SELECT UCASE(Cafe), LCASE(Menu) from sandwich"
                }
            ]
        },
        {
            "state": {
                "start": 6,
                "end": 6,
                "language": "mysql",
                "result": {
                    "type": "resultIds",
                    "list": [
                        "bf16add3-3d1b-4fd2-8f72-87b2c4380864"
                    ]
                },
                "currentHeight": 36,
                "statements": [
                    {
                        "delimiter": ";",
                        "span": {
                            "start": 0,
                            "length": 83
                        },
                        "contentStart": 0,
                        "state": 0
                    }
                ]
            },
            "data": [
                {
                    "tabId": "e706df21-6856-490e-f719-1d86ecb4e120",
                    "resultId": "bf16add3-3d1b-4fd2-8f72-87b2c4380864",
                    "rows": [
                        {
                            "0": 10,
                            "1": 32,
                            "2": "Grilled Laughing Bird Shrimp and",
                            "3": "d"
                        }
                    ],
                    "columns": [
                        {
                            "title": "Rank_id",
                            "field": "0",
                            "dataType": {
                                "type": 4
                            }
                        },
                        {
                            "title": "LENGTH(Menu)",
                            "field": "1",
                            "dataType": {
                                "type": 4
                            }
                        },
                        {
                            "title": "Menu",
                            "field": "2",
                            "dataType": {
                                "type": 17
                            }
                        },
                        {
                            "title": "MID(Menu, -1)",
                            "field": "3",
                            "dataType": {
                                "type": 17
                            }
                        }
                    ],
                    "executionInfo": {
                        "text": "OK, 1 record retrieved in 7.03ms"
                    },
                    "totalRowCount": 1,
                    "hasMoreRows": false,
                    "currentPage": 0,
                    "index": 0,
                    "sql": "SELECT Rank_id, LENGTH(Menu), Menu, MID(Menu, -1) from sandwich where RANK_id = 10"
                }
            ]
        },
        {
            "state": {
                "start": 7,
                "end": 7,
                "language": "mysql",
                "result": {
                    "type": "resultIds",
                    "list": [
                        "adb507bd-32d0-4cbe-c3d2-d624376406c1"
                    ]
                },
                "currentHeight": 36,
                "statements": [
                    {
                        "delimiter": ";",
                        "span": {
                            "start": 0,
                            "length": 35
                        },
                        "contentStart": 0,
                        "state": 0
                    },
                    {
                        "delimiter": ";",
                        "span": {
                            "start": 35,
                            "length": 1
                        },
                        "contentStart": 34,
                        "state": 3
                    }
                ]
            },
            "data": [
                {
                    "tabId": "e706df21-6856-490e-f719-1d86ecb4e120",
                    "resultId": "adb507bd-32d0-4cbe-c3d2-d624376406c1",
                    "rows": [
                        {
                            "0": 3
                        },
                        {
                            "0": 13
                        },
                        {
                            "0": 17
                        },
                        {
                            "0": 10
                        },
                        {
                            "0": 4
                        },
                        {
                            "0": 27
                        },
                        {
                            "0": 12
                        },
                        {
                            "0": 19
                        },
                        {
                            "0": 15
                        },
                        {
                            "0": 32
                        },
                        {
                            "0": 23
                        },
                        {
                            "0": 13
                        },
                        {
                            "0": 11
                        },
                        {
                            "0": 11
                        },
                        {
                            "0": 20
                        },
                        {
                            "0": 12
                        },
                        {
                            "0": 11
                        },
                        {
                            "0": 11
                        },
                        {
                            "0": 7
                        },
                        {
                            "0": 9
                        },
                        {
                            "0": 17
                        },
                        {
                            "0": 8
                        },
                        {
                            "0": 23
                        },
                        {
                            "0": 17
                        },
                        {
                            "0": 12
                        },
                        {
                            "0": 8
                        },
                        {
                            "0": 9
                        },
                        {
                            "0": 10
                        },
                        {
                            "0": 8
                        },
                        {
                            "0": 16
                        },
                        {
                            "0": 31
                        },
                        {
                            "0": 10
                        },
                        {
                            "0": 16
                        },
                        {
                            "0": 12
                        },
                        {
                            "0": 6
                        },
                        {
                            "0": 26
                        },
                        {
                            "0": 15
                        },
                        {
                            "0": 14
                        },
                        {
                            "0": 13
                        },
                        {
                            "0": 14
                        },
                        {
                            "0": 10
                        },
                        {
                            "0": 9
                        },
                        {
                            "0": 32
                        },
                        {
                            "0": 16
                        },
                        {
                            "0": 6
                        },
                        {
                            "0": 5
                        },
                        {
                            "0": 20
                        },
                        {
                            "0": 10
                        },
                        {
                            "0": 15
                        },
                        {
                            "0": 10
                        }
                    ],
                    "columns": [
                        {
                            "title": "length(Menu)",
                            "field": "0",
                            "dataType": {
                                "type": 4
                            }
                        }
                    ],
                    "executionInfo": {
                        "text": "OK, 50 records retrieved in 4.442ms"
                    },
                    "totalRowCount": 50,
                    "hasMoreRows": false,
                    "currentPage": 0,
                    "index": 0,
                    "sql": "SELECT length(Menu) from sandwich "
                }
            ]
        },
        {
            "state": {
                "start": 8,
                "end": 8,
                "language": "mysql",
                "result": {
                    "type": "resultIds",
                    "list": [
                        "75a0d670-60dd-4a35-b6f0-b8c98352fbce"
                    ]
                },
                "currentHeight": 36,
                "statements": [
                    {
                        "delimiter": ";",
                        "span": {
                            "start": 0,
                            "length": 40
                        },
                        "contentStart": 0,
                        "state": 0
                    }
                ]
            },
            "data": [
                {
                    "tabId": "e706df21-6856-490e-f719-1d86ecb4e120",
                    "resultId": "75a0d670-60dd-4a35-b6f0-b8c98352fbce",
                    "rows": [
                        {
                            "0": "13.9600"
                        }
                    ],
                    "columns": [
                        {
                            "title": "AVG(length(Menu))",
                            "field": "0",
                            "dataType": {
                                "type": 10
                            }
                        }
                    ],
                    "executionInfo": {
                        "text": "OK, 1 record retrieved in 4.409ms"
                    },
                    "totalRowCount": 1,
                    "hasMoreRows": false,
                    "currentPage": 0,
                    "index": 0,
                    "sql": "SELECT AVG(length(Menu)) from sandwich "
                }
            ]
        },
        {
            "state": {
                "start": 9,
                "end": 9,
                "language": "mysql",
                "result": {
                    "type": "resultIds",
                    "list": [
                        "e6c6e371-36b1-4a09-d60c-299abb6894cb"
                    ]
                },
                "currentHeight": 351.984375,
                "statements": [
                    {
                        "delimiter": ";",
                        "span": {
                            "start": 0,
                            "length": 24
                        },
                        "contentStart": 0,
                        "state": 0
                    }
                ]
            },
            "data": [
                {
                    "tabId": "e706df21-6856-490e-f719-1d86ecb4e120",
                    "resultId": "e6c6e371-36b1-4a09-d60c-299abb6894cb",
                    "rows": [
                        {
                            "0": 1,
                            "1": "타이거주유소",
                            "2": "서울 은평구 수색로 188(중산동)",
                            "3": 1484,
                            "4": "N",
                            "5": "SK에너지",
                            "6": "은평구"
                        },
                        {
                            "0": 2,
                            "1": "(주)명연에너지",
                            "2": "서울 은평구 수색로 236(수색동)",
                            "3": 1485,
                            "4": "Y",
                            "5": "현대오일뱅크",
                            "6": "은평구"
                        },
                        {
                            "0": 3,
                            "1": "성락주유소",
                            "2": "서울 영등포구 가마산로 414(신길동)",
                            "3": 1498,
                            "4": "Y",
                            "5": "S-OIL",
                            "6": "영등포구"
                        },
                        {
                            "0": 4,
                            "1": "(주)MS주유소",
                            "2": "서울특별시 영등포구 대림로 230(대림동)",
                            "3": 1498,
                            "4": "N",
                            "5": "현대오일뱅크",
                            "6": "영등포구"
                        },
                        {
                            "0": 5,
                            "1": "쌍문주유소",
                            "2": "서울특별시 도봉구 도봉로 547(쌍문동)",
                            "3": 1509,
                            "4": "Y",
                            "5": "S-OIL",
                            "6": "도봉구"
                        },
                        {
                            "0": 6,
                            "1": "21세기주유소",
                            "2": "서울 동작구 시흥대로 616(신대방동)",
                            "3": 1598,
                            "4": "Y",
                            "5": "SK에너지",
                            "6": "동작구"
                        },
                        {
                            "0": 7,
                            "1": "살피재주유소",
                            "2": "서울 동작구 상도로 334(상도동)",
                            "3": 1635,
                            "4": "N",
                            "5": "SK에너지",
                            "6": "동작구"
                        },
                        {
                            "0": 8,
                            "1": "뉴서울(강남)",
                            "2": "서울 강남구 언주로 716(논현동)",
                            "3": 2160,
                            "4": "N",
                            "5": "SK에너지",
                            "6": "강남구"
                        },
                        {
                            "0": 9,
                            "1": "신길주유소",
                            "2": "서울특별시 영등포구 신길로 74(신길동)",
                            "3": 1498,
                            "4": "Y",
                            "5": "GS칼텍스",
                            "6": "영등포구"
                        }
                    ],
                    "columns": [
                        {
                            "title": "ID",
                            "field": "0",
                            "dataType": {
                                "type": 4
                            }
                        },
                        {
                            "title": "상호",
                            "field": "1",
                            "dataType": {
                                "type": 17
                            }
                        },
                        {
                            "title": "주소",
                            "field": "2",
                            "dataType": {
                                "type": 17
                            }
                        },
                        {
                            "title": "가격",
                            "field": "3",
                            "dataType": {
                                "type": 4
                            }
                        },
                        {
                            "title": "셀프",
                            "field": "4",
                            "dataType": {
                                "type": 17
                            }
                        },
                        {
                            "title": "상표",
                            "field": "5",
                            "dataType": {
                                "type": 17
                            }
                        },
                        {
                            "title": "구",
                            "field": "6",
                            "dataType": {
                                "type": 17
                            }
                        }
                    ],
                    "executionInfo": {
                        "text": "OK, 9 records retrieved in 4.567ms"
                    },
                    "totalRowCount": 9,
                    "hasMoreRows": false,
                    "currentPage": 0,
                    "index": 0,
                    "sql": "SELECT * from oil_price"
                }
            ]
        },
        {
            "state": {
                "start": 10,
                "end": 10,
                "language": "mysql",
                "result": {
                    "type": "resultIds",
                    "list": [
                        "bc048c8b-29c1-406b-d0bf-b76a476a1cb4"
                    ]
                },
                "currentHeight": 348.65625,
                "statements": [
                    {
                        "delimiter": ";",
                        "span": {
                            "start": 0,
                            "length": 36
                        },
                        "contentStart": 0,
                        "state": 0
                    }
                ]
            },
            "data": [
                {
                    "tabId": "e706df21-6856-490e-f719-1d86ecb4e120",
                    "resultId": "bc048c8b-29c1-406b-d0bf-b76a476a1cb4",
                    "rows": [
                        {
                            "0": 1500
                        },
                        {
                            "0": 1500
                        },
                        {
                            "0": 1500
                        },
                        {
                            "0": 1500
                        },
                        {
                            "0": 1500
                        },
                        {
                            "0": 1600
                        },
                        {
                            "0": 1600
                        },
                        {
                            "0": 2200
                        },
                        {
                            "0": 1500
                        }
                    ],
                    "columns": [
                        {
                            "title": "ROUND(가격, -2)",
                            "field": "0",
                            "dataType": {
                                "type": 4
                            }
                        }
                    ],
                    "executionInfo": {
                        "text": "OK, 9 records retrieved in 6.404ms"
                    },
                    "totalRowCount": 9,
                    "hasMoreRows": false,
                    "currentPage": 0,
                    "index": 0,
                    "sql": "SELECT ROUND(가격, -2) from oil_price"
                }
            ]
        },
        {
            "state": {
                "start": 11,
                "end": 11,
                "language": "mysql",
                "result": {
                    "type": "resultIds",
                    "list": [
                        "58b9d1cb-2f3e-4f35-feb1-e13dd7e55ab7"
                    ]
                },
                "currentHeight": 36,
                "statements": [
                    {
                        "delimiter": ";",
                        "span": {
                            "start": 0,
                            "length": 68
                        },
                        "contentStart": 0,
                        "state": 0
                    }
                ]
            },
            "data": [
                {
                    "tabId": "e706df21-6856-490e-f719-1d86ecb4e120",
                    "resultId": "58b9d1cb-2f3e-4f35-feb1-e13dd7e55ab7",
                    "rows": [
                        {
                            "0": "2,160",
                            "1": 2160
                        }
                    ],
                    "columns": [
                        {
                            "title": "format(가격, 0)",
                            "field": "0",
                            "dataType": {
                                "type": 17
                            }
                        },
                        {
                            "title": "가격",
                            "field": "1",
                            "dataType": {
                                "type": 4
                            }
                        }
                    ],
                    "executionInfo": {
                        "text": "OK, 1 record retrieved in 5.181ms"
                    },
                    "totalRowCount": 1,
                    "hasMoreRows": false,
                    "currentPage": 0,
                    "index": 0,
                    "sql": "select format(가격, 0), 가격 from oil_price where round(가격, -2) >= 2000"
                }
            ]
        },
        {
            "state": {
                "start": 12,
                "end": 12,
                "language": "mysql",
                "result": {
                    "type": "resultIds",
                    "list": [
                        "c6f0bb0e-aa3b-47f3-8565-67327d032ea3"
                    ]
                },
                "currentHeight": 348.65625,
                "statements": [
                    {
                        "delimiter": ";",
                        "span": {
                            "start": 0,
                            "length": 0
                        },
                        "contentStart": 0,
                        "state": 3
                    }
                ]
            },
            "data": [
                {
                    "tabId": "e706df21-6856-490e-f719-1d86ecb4e120",
                    "resultId": "c6f0bb0e-aa3b-47f3-8565-67327d032ea3",
                    "rows": [
                        {
                            "0": 1,
                            "1": "타이거주유소",
                            "2": "서울 은평구 수색로 188(중산동)",
                            "3": 1484,
                            "4": "N",
                            "5": "SK에너지",
                            "6": "은평구"
                        },
                        {
                            "0": 2,
                            "1": "(주)명연에너지",
                            "2": "서울 은평구 수색로 236(수색동)",
                            "3": 1485,
                            "4": "Y",
                            "5": "현대오일뱅크",
                            "6": "은평구"
                        },
                        {
                            "0": 3,
                            "1": "성락주유소",
                            "2": "서울 영등포구 가마산로 414(신길동)",
                            "3": 1498,
                            "4": "Y",
                            "5": "S-OIL",
                            "6": "영등포구"
                        },
                        {
                            "0": 4,
                            "1": "(주)MS주유소",
                            "2": "서울특별시 영등포구 대림로 230(대림동)",
                            "3": 1498,
                            "4": "N",
                            "5": "현대오일뱅크",
                            "6": "영등포구"
                        },
                        {
                            "0": 5,
                            "1": "쌍문주유소",
                            "2": "서울특별시 도봉구 도봉로 547(쌍문동)",
                            "3": 1509,
                            "4": "Y",
                            "5": "S-OIL",
                            "6": "도봉구"
                        },
                        {
                            "0": 6,
                            "1": "21세기주유소",
                            "2": "서울 동작구 시흥대로 616(신대방동)",
                            "3": 1598,
                            "4": "Y",
                            "5": "SK에너지",
                            "6": "동작구"
                        },
                        {
                            "0": 7,
                            "1": "살피재주유소",
                            "2": "서울 동작구 상도로 334(상도동)",
                            "3": 1635,
                            "4": "N",
                            "5": "SK에너지",
                            "6": "동작구"
                        },
                        {
                            "0": 8,
                            "1": "뉴서울(강남)",
                            "2": "서울 강남구 언주로 716(논현동)",
                            "3": 2160,
                            "4": "N",
                            "5": "SK에너지",
                            "6": "강남구"
                        },
                        {
                            "0": 9,
                            "1": "신길주유소",
                            "2": "서울특별시 영등포구 신길로 74(신길동)",
                            "3": 1498,
                            "4": "Y",
                            "5": "GS칼텍스",
                            "6": "영등포구"
                        }
                    ],
                    "columns": [
                        {
                            "title": "ID",
                            "field": "0",
                            "dataType": {
                                "type": 4
                            }
                        },
                        {
                            "title": "상호",
                            "field": "1",
                            "dataType": {
                                "type": 17
                            }
                        },
                        {
                            "title": "주소",
                            "field": "2",
                            "dataType": {
                                "type": 17
                            }
                        },
                        {
                            "title": "가격",
                            "field": "3",
                            "dataType": {
                                "type": 4
                            }
                        },
                        {
                            "title": "셀프",
                            "field": "4",
                            "dataType": {
                                "type": 17
                            }
                        },
                        {
                            "title": "상표",
                            "field": "5",
                            "dataType": {
                                "type": 17
                            }
                        },
                        {
                            "title": "구",
                            "field": "6",
                            "dataType": {
                                "type": 17
                            }
                        }
                    ],
                    "executionInfo": {
                        "text": "OK, 9 records retrieved in 3.993ms"
                    },
                    "totalRowCount": 9,
                    "hasMoreRows": false,
                    "currentPage": 0,
                    "index": 0,
                    "sql": "SELECT * from oil_price"
                }
            ]
        },
        {
            "state": {
                "start": 13,
                "end": 13,
                "language": "mysql",
                "currentHeight": 180,
                "statements": [
                    {
                        "delimiter": ";",
                        "span": {
                            "start": 0,
                            "length": 0
                        },
                        "contentStart": 0,
                        "state": 0
                    }
                ]
            },
            "data": []
        }
    ]
}