################################################################################
# micro T-Kernel 3.00.03  makefile
################################################################################

OBJS += \
./mtkernel_3/lib/nnablart/functions/implements/math/abs.o \
./mtkernel_3/lib/nnablart/functions/implements/math/batch_matmul.o \
./mtkernel_3/lib/nnablart/functions/implements/math/exp.o \
./mtkernel_3/lib/nnablart/functions/implements/math/identity.o \
./mtkernel_3/lib/nnablart/functions/implements/math/log.o \
./mtkernel_3/lib/nnablart/functions/implements/math/round.o

C_DEPS += \
./mtkernel_3/lib/nnablart/functions/implements/math/abs.d \
./mtkernel_3/lib/nnablart/functions/implements/math/batch_matmul.d \
./mtkernel_3/lib/nnablart/functions/implements/math/exp.d \
./mtkernel_3/lib/nnablart/functions/implements/math/identity.d \
./mtkernel_3/lib/nnablart/functions/implements/math/log.d \
./mtkernel_3/lib/nnablart/functions/implements/math/round.d

mtkernel_3/lib/nnablart/functions/implements/math/%.o: ../lib/nnabla_c_runtime/src/functions/implements/math/%.c
	@echo 'Building file: $<'
	$(GCC) $(CFLAGS) -D$(TARGET) $(INCPATH) -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '
