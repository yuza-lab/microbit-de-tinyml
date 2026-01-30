################################################################################
# micro T-Kernel 3.00.03  makefile
################################################################################

OBJS += \
./mtkernel_3/lib/nnablart/functions/implements/logical/maximum2.o \
./mtkernel_3/lib/nnablart/functions/implements/logical/maximum_scalar.o \
./mtkernel_3/lib/nnablart/functions/implements/logical/minimum2.o \
./mtkernel_3/lib/nnablart/functions/implements/logical/minimum_scalar.o \
./mtkernel_3/lib/nnablart/functions/implements/logical/sign.o

C_DEPS += \
./mtkernel_3/lib/nnablart/functions/implements/logical/maximum2.d \
./mtkernel_3/lib/nnablart/functions/implements/logical/maximum_scalar.d \
./mtkernel_3/lib/nnablart/functions/implements/logical/minimum2.d \
./mtkernel_3/lib/nnablart/functions/implements/logical/minimum_scalar.d \
./mtkernel_3/lib/nnablart/functions/implements/logical/sign.d

mtkernel_3/lib/nnablart/functions/implements/logical/%.o: ../lib/nnabla_c_runtime/src/functions/implements/logical/%.c
	@echo 'Building file: $<'
	$(GCC) $(CFLAGS) -D$(TARGET) $(INCPATH) -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '
