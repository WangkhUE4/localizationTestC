REM 1、使用之前请先配置好下面几项，运行一次编辑器下的Gater。
REM 2、此一键导入脚本是纯cmd的。如果已经打开了编辑器，那会失败。这种情况应该用二键脚本。

set engine=G:\UnrealEngine-5.0.3-release

set projectpath=E:\test\UE4\localizationTestC

set projectname=localizationTestC
set xlsxname=LocalizationTest


Call convert_xlsx_Locolization.exe ./%xlsxname%.xlsx
Call %engine%\Engine\Binaries\Win64\UnrealEditor-Cmd.exe %projectpath%/%projectname%.uproject -platform=Win64 -run=ImportStringTable -From=%projectpath%/Script/convert_xlsx_Locolization/%xlsxname%.csv -To="/Game/Localization/StringTable/%xlsxname%"

Call %engine%\Engine\Build\BatchFiles\RunUAT.bat Localize -UEProjectRoot="" -UEProjectDirectory=%projectpath% -UEProjectName=%projectname% -LocalizationSteps="Gather" -LocalizationProjectNames="Game"
Call %engine%\Engine\Build\BatchFiles\RunUAT.bat Localize -UEProjectRoot="" -UEProjectDirectory=%projectpath% -UEProjectName=%projectname% -LocalizationSteps="Export" -LocalizationProjectNames="Game"
call modify_Po.exe ./%xlsxname%.xlsx %projectpath%
Call %engine%\Engine\Build\BatchFiles\RunUAT.bat Localize -UEProjectRoot="" -UEProjectDirectory=%projectpath% -UEProjectName=%projectname% -LocalizationSteps="Import" -LocalizationProjectNames="Game"
Call %engine%\Engine\Build\BatchFiles\RunUAT.bat Localize -UEProjectRoot="" -UEProjectDirectory=%projectpath% -UEProjectName=%projectname% -LocalizationSteps="Compile" -LocalizationProjectNames="Game"



echo ----------------------------------Success----------------------------------------
pause














                









                