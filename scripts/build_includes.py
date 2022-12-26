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
    print("Include folder creating...")

    out_dir += f"{slash}include{slash}"

    error_chars = ["/\\", "\\/", "//", "\\\\"]
    for char in error_chars:
        while root_dir.find(char) != -1:
            root_dir = root_dir.replace(char, slash)
        while root_dir.find(char) != -1:
            out_dir = out_dir.replace(char, slash)

    engine_project_root = root_dir + f"{slash}UrbanEngine"
    engine_project_src_dir = engine_project_root + f"{slash}src"
    engine_project_platform_dir = engine_project_src_dir + f"{slash}UrbanEngine{slash}Platform"
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
        # Skip platform headers
        if engine_project_platform_dir in root:
            continue

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
    root_dir = os.getcwd() + f"{slash}..{slash}"
    out_dir = root_dir + f"build{slash}"
    copy_headers(root_dir, out_dir)
