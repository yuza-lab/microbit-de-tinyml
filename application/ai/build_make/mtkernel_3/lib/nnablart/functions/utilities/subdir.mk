################################################################################
# micro T-Kernel 3.00.03  makefile
################################################################################

OBJS += \
./mtkernel_3/lib/nnablart/functions/utilities/accessor.o \
./mtkernel_3/lib/nnablart/functions/utilities/fixedpoint.o \
./mtkernel_3/lib/nnablart/functions/utilities/list.o \
./mtkernel_3/lib/nnablart/functions/utilities/shape.o 

C_DEPS += \
./mtkernel_3/lib/nnablart/functions/utilities/accessor.d \
./mtkernel_3/lib/nnablart/functions/utilities/fixedpoint.d \
./mtkernel_3/lib/nnablart/functions/utilities/list.d \
./mtkernel_3/lib/nnablart/functions/utilities/shape.d 

mtkernel_3/lib/nnablart/functions/utilities/%.o: ../lib/nnabla_c_runtime/src/functions/utilities/%.c
	@echo 'Building file: $<'
	$(GCC) $(CFLAGS) -D$(TARGET) $(INCPATH) -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '
