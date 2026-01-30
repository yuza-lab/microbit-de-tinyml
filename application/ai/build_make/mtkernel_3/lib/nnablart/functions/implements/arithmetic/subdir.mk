################################################################################
# micro T-Kernel 3.00.03  makefile
################################################################################

OBJS += \
./mtkernel_3/lib/nnablart/functions/implements/arithmetic/add2.o \
./mtkernel_3/lib/nnablart/functions/implements/arithmetic/add_scalar.o \
./mtkernel_3/lib/nnablart/functions/implements/arithmetic/arithmetic.o \
./mtkernel_3/lib/nnablart/functions/implements/arithmetic/arithmetic_fixed.o \
./mtkernel_3/lib/nnablart/functions/implements/arithmetic/arithmetic_generic.o \
./mtkernel_3/lib/nnablart/functions/implements/arithmetic/div2.o \
./mtkernel_3/lib/nnablart/functions/implements/arithmetic/mul2.o \
./mtkernel_3/lib/nnablart/functions/implements/arithmetic/mul_scalar.o \
./mtkernel_3/lib/nnablart/functions/implements/arithmetic/pow2.o \
./mtkernel_3/lib/nnablart/functions/implements/arithmetic/pow_scalar.o \
./mtkernel_3/lib/nnablart/functions/implements/arithmetic/r_div_scalar.o \
./mtkernel_3/lib/nnablart/functions/implements/arithmetic/r_pow_scalar.o \
./mtkernel_3/lib/nnablart/functions/implements/arithmetic/r_sub_scalar.o \
./mtkernel_3/lib/nnablart/functions/implements/arithmetic/sub2.o

C_DEPS += \
./mtkernel_3/lib/nnablart/functions/implements/arithmetic/add2.d \
./mtkernel_3/lib/nnablart/functions/implements/arithmetic/add_scalar.d \
./mtkernel_3/lib/nnablart/functions/implements/arithmetic/arithmetic.d \
./mtkernel_3/lib/nnablart/functions/implements/arithmetic/arithmetic_fixed.d \
./mtkernel_3/lib/nnablart/functions/implements/arithmetic/arithmetic_generic.d \
./mtkernel_3/lib/nnablart/functions/implements/arithmetic/div2.d \
./mtkernel_3/lib/nnablart/functions/implements/arithmetic/mul2.d \
./mtkernel_3/lib/nnablart/functions/implements/arithmetic/mul_scalar.d \
./mtkernel_3/lib/nnablart/functions/implements/arithmetic/pow2.d \
./mtkernel_3/lib/nnablart/functions/implements/arithmetic/pow_scalar.d \
./mtkernel_3/lib/nnablart/functions/implements/arithmetic/r_div_scalar.d \
./mtkernel_3/lib/nnablart/functions/implements/arithmetic/r_pow_scalar.d \
./mtkernel_3/lib/nnablart/functions/implements/arithmetic/r_sub_scalar.d \
./mtkernel_3/lib/nnablart/functions/implements/arithmetic/sub2.d

mtkernel_3/lib/nnablart/functions/implements/arithmetic/%.o: ../lib/nnabla_c_runtime/src/functions/implements/arithmetic/%.c
	@echo 'Building file: $<'
	$(GCC) $(CFLAGS) -D$(TARGET) $(INCPATH) -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '
