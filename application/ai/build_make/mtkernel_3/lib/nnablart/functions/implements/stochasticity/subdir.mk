################################################################################
# micro T-Kernel 3.00.03  makefile
################################################################################

OBJS += \
./mtkernel_3/lib/nnablart/functions/implements/stochasticity/dropout.o

C_DEPS += \
./mtkernel_3/lib/nnablart/functions/implements/stochasticity/dropout.d

mtkernel_3/lib/nnablart/functions/implements/stochasticity/%.o: ../lib/nnabla_c_runtime/src/functions/implements/stochasticity/%.c
	@echo 'Building file: $<'
	$(GCC) $(CFLAGS) -D$(TARGET) $(INCPATH) -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '
