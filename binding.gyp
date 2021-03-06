{
	"targets": [
		{
			"target_name" : "format.handler",
			"type" : "static_library",
			"sources" : [
				"./format.handler/BinFormat.cpp",
				"./format.handler/TextFormat.cpp"
			],
			"include_dirs": [
				"./include"
			],
			"conditions": [
				["OS==\"linux\"", {
					"cflags": [
						"-g",
						"-m32",
						"-std=c++11",
						"-D__cdecl=''",
						"-D__stdcall=''"
					],
          "include_dirs": [
              "<!(echo $RIVER_SDK_DIR)/include"
            ]
				}
				]
			]
		},
		{
			"target_name" : "logger",
			"type" : "static_library",
			"sources" : [
				"./logger/AbstractLog.cpp",
				"./logger/FileLog.cpp",
				"./logger/Logger.cpp"
			],
			"include_dirs" : [
				"./include"
			],
			"conditions": [
				["OS==\"linux\"", {
					"cflags": [
						"-g",
						"-m32",
						"-std=c++11",
						"-D__cdecl=''",
						"-D__stdcall=''"
						],
            "include_dirs": [
              "<!(echo $RIVER_SDK_DIR)/include"
            ]
					}
				]
			]
		}
	]
}
