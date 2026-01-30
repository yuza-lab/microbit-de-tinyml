################################################################################
# micro T-Kernel 3.00.05  makefile
################################################################################

OBJS += \
./mtkernel_3/lib/nnablart/runtime/runtime.o \
./mtkernel_3/lib/nnablart/runtime/runtime_internal.o \
./mtkernel_3/lib/nnablart/runtime/function_context.o 

C_DEPS += \
./mtkernel_3/lib/nnablart/runtime/runtime.d \
./mtkernel_3/lib/nnablart/runtime/runtime_internal.d \
./mtkernel_3/lib/nnablart/runtime/function_context.d 

mtkernel_3/lib/nnablart/runtime/%.o: ../lib/nnabla_c_runtime/src/runtime/%.c
	@echo 'Building file: $<'
	$(GCC) $(CFLAGS) -D$(TARGET) $(INCPATH) -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '
