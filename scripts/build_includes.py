import os
import sys
import shutil
import platform

slash = None
if platform.system() == 'Windows':
    slash = "\\"
elif platform.system() == "Linux":
    slash = "/"

def copy_headers(root_dir: str, out_dir: str):
    if out_dir == None:
        if platform.system() == "Windows":
            out_dir = root_dir + f"{slash}bin{slash}Debug-windows{slash}UrbanEngine"
        elif platform.system() == "Linux":
            out_dir = root_dir + f"{slash}build"
    out_dir += f"{slash}include{slash}"

    if root_dir[-1] == slash:
        root_dir = root_dir[0:len(root_dir) - 1]

    error_chars = ["/\\", "\\/", "//", "\\\\"]
    for char in error_chars:
        while root_dir.find(char) != -1:
            root_dir = root_dir.replace(char, slash)
        while root_dir.find(char) != -1:
            out_dir = out_dir.replace(char, slash)

    engine_project_root = root_dir + f"{slash}UrbanEngine"
    engine_project_src_dir = engine_project_root + f"{slash}src"
    engine_project_vendor_dir = engine_project_root + f"{slash}vendor"

    glm_root_dir = engine_project_vendor_dir + f"{slash}glm"
    glm_src_dir = glm_root_dir + f"{slash}glm"

    files_will_copy = {
        "src": [],
        "glm": []
    }
    file_roots = set()

    # Scan src folder
    for root, sub_folders, files in os.walk(engine_project_src_dir):
        for f in files:
            file_name, file_extension = os.path.splitext(root + f"{slash}" + f)
            # Skip precompiled header
            if f == "urbanpch.h":
                continue
            if file_extension in [".h", ".hpp", ".inl"]:
                files_will_copy["src"].append(file_name + file_extension)
                file_roots.add(out_dir + root[len(engine_project_src_dir) + 1:])

    # Scan glm (it is comment because there is no glm yet)
    """
    for root, sub_folders, files in os.walk(glm_src_dir):
        for f in files:
            file_name, file_extension = os.path.splitext(root + slash + f)
            if file_extension == ".h" or file_extension == ".hpp" or file_extension == ".inl":
                files_will_copy["glm"].append(file_name + file_extension)
                file_roots.add(out_dir + root[len(glm_root_dir) + 1:])
    """

    for r in file_roots:
        os.makedirs(r, exist_ok=True)

    # Copy src
    i = 0
    for f in files_will_copy["src"]:
        shutil.copy2(f, os.path.dirname(out_dir + f[len(engine_project_src_dir) + 1:]) + f"{slash}")
        i += 1
        print(f"({int(100 * i / (len(files_will_copy['src']) + len(files_will_copy['glm'])))}%)\t\"{f}\" copied!")

    # Copy glm (there is no glm yet)
    """
    for f in files_will_copy["glm"]:
        shutil.copy2(f, os.path.dirname(out_dir + f[len(glm_root_dir):]))
    """

if __name__ == "__main__":
    working_dir = os.getcwd()
    root_dir = None
    out_dir = None

    if len(sys.argv) == 1:
        if working_dir[::-1][0:len(f"{slash}UrbanEngine{slash}scripts")][::-1] == f"{slash}UrbanEngine{slash}scripts":
            root_dir = working_dir[0:len(working_dir) - len(f"{slash}scripts")]
    else:
        argument_mode = ""
        for arg in sys.argv:
            if arg == "-r":
                argument_mode = "root"
                continue
            elif arg == "-o":
                argument_mode = "out"
                continue

            if argument_mode == "root":
                root_dir = arg
            elif argument_mode == "out":
                out_dir = arg

    if root_dir != None:
        copy_headers(root_dir, out_dir)
    else:
        if platform.system() == "Windows":
            print(
                f"Please enter root folder with \"-r\" parameter and output folder with \"-o\" parameter.\nExample Usage:\npy scripts{slash}build_includes.py -r \"C:{slash}Projects{slash}UrbanEngine\" -o \"C:{slash}Projects{slash}UrbanEngine{slash}bin{slash}Release-windows{slash}UrbanEngine\"")
        elif platform.system() == "Linux":
            print(
                f"Please enter root folder with \"-r\" parameter and output folder with \"-o\" parameter.\nExample Usage:\npython3 scripts{slash}build_includes.py -r \"~{slash}Projects{slash}UrbanEngine\" -o \"~{slash}Projects{slash}UrbanEngine{slash}build\"")
