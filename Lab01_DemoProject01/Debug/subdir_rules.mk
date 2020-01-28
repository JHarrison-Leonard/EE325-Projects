################################################################################
# Automatically-generated file. Do not edit!
################################################################################

SHELL = cmd.exe

# Each subdirectory must supply rules for building sources it contributes
%.obj: ../%.c $(GEN_OPTS) | $(GEN_FILES)
	@echo 'Building file: "$<"'
	@echo 'Invoking: MSP430 Compiler'
	"C:/ti/ccs901/ccs/tools/compiler/ti-cgt-msp430_18.12.1.LTS/bin/cl430" -vmsp --code_model=small --data_model=small -Ooff --use_hw_mpy=16 --include_path="C:/ti/ccs901/ccs/ccs_base/msp430/include" --include_path="D:/CPE325/Projects/Lab01_DemoProject01" --include_path="C:/ti/ccs901/ccs/tools/compiler/ti-cgt-msp430_18.12.1.LTS/include" --advice:power="all" --define=__MSP430FG4617__ -g --c99 --printf_support=full --diag_warning=225 --diag_wrap=off --display_error_number --preproc_with_compile --preproc_dependency="$(basename $(<F)).d_raw" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: "$<"'
	@echo ' '

twofact.obj: ../twofact.c $(GEN_OPTS) | $(GEN_FILES)
	@echo 'Building file: "$<"'
	@echo 'Invoking: MSP430 Compiler'
	"C:/ti/ccs901/ccs/tools/compiler/ti-cgt-msp430_18.12.1.LTS/bin/cl430" -vmsp --code_model=small --data_model=small -Ooff --use_hw_mpy=16 --include_path="C:/ti/ccs901/ccs/ccs_base/msp430/include" --include_path="D:/CPE325/Projects/Lab01_DemoProject01" --include_path="C:/ti/ccs901/ccs/tools/compiler/ti-cgt-msp430_18.12.1.LTS/include" --advice:power="all" --define=__MSP430FG4617__ -g --c99 --printf_support=full --diag_warning=225 --diag_wrap=off --display_error_number --preproc_with_compile --preproc_dependency="$(basename $(<F)).d_raw" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: "$<"'
	@echo ' '


