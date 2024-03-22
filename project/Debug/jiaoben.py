import subprocess

# 地图文件路径
maps = ['my','1','2','-3.7','-3.8','-3.9','-3.10','-3.11','-3.12','-3.13']

# 要分析的程序路径
projects = ['wsh.exe']
# 假设PreliminaryJudge是一个命令行工具，我们调用它并传递参数
# 注意：这里需要替换为实际的命令行工具名称和参数格式
for project in projects:
    print(project)
    for map in maps:
        map_file_path = fr"C:\Users\86150\Desktop\leezhou2\Huawei_Chanllenge_Preliminary\WindowsRelease\maps\map{map}.txt"
        print(map_file_path)
        command = [r"C:\Users\86150\Desktop\leezhou2\Huawei_Chanllenge_Preliminary\WindowsRelease\PreliminaryJudge.exe", "-m", map_file_path, project,'-l', 'NONE','-s','42']
        result = subprocess.run(command, check=True)
        if result.returncode == 0:
            print("执行成功")
        else:
            print(f"执行失败，返回码：{result.returncode}")
    # 执行命令并等待它完成