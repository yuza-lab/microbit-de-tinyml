################################################################################
# micro T-Kernel 3.00.03  makefile
################################################################################

OBJS += \
./mtkernel_3/lib/nnablart/nnablart/dump.o \
./mtkernel_3/lib/nnablart/nnablart/dump_function.o 

C_DEPS += \
./mtkernel_3/lib/nnablart/nnablart/dump.d \
./mtkernel_3/lib/nnablart/nnablart/dump_function.d 

mtkernel_3/lib/nnablart/nnablart/%.o: ../lib/nnabla_c_runtime/src/nnablart/%.c
	@echo 'Building file: $<'
	$(GCC) $(CFLAGS) -D$(TARGET) $(INCPATH) -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '
