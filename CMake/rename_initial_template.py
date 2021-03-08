import sys, os, datetime

templatename = input("Template name:")
templatename = templatename.replace(" ", "")


def genTemplates():
    global templatename

    files = [
        "README.md",
        "CMakeLists.txt",
        "CMake/CMakeLists.txt",
        "CMake/Application.cmake",
        "CMake/Configure.cmake",
        "Bin/Readme.md",
        "Extern/CMakeLists.txt",
        "Source/CMakeLists.txt",
        "Source/Main.cpp",
        "Source/Application.cpp",
        "Test/CMakeLists.txt",
    ]

    patterns = [".yml", ".txt", ".cmake", "Jenkinsfile", ".cpp", ".md"]
    root = os.getcwd()

    for file in files:
        full_path = root + os.sep + file
        full_path = full_path.replace("\\", os.sep)

        if os.path.isfile(full_path):

            found = False
            for pat in patterns:
                if full_path.find(pat) != -1:
                    found = True
                    break
            if found:
                print("Found", full_path)
                fp = open(full_path, "r")
                buf = fp.read()
                fp.close()
                buf = buf.replace("GraphicsTemplate", templatename)
                fp = open(full_path, "w")
                fp.write(buf)
                fp.close()


genTemplates()
