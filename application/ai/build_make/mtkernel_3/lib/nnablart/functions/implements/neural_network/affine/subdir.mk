################################################################################
# micro T-Kernel 3.00.03  makefile
################################################################################

OBJS += \
./mtkernel_3/lib/nnablart/functions/implements/neural_network/affine/affine.o \
./mtkernel_3/lib/nnablart/functions/implements/neural_network/affine/affine_fixed16.o \
./mtkernel_3/lib/nnablart/functions/implements/neural_network/affine/affine_fixed8.o \
./mtkernel_3/lib/nnablart/functions/implements/neural_network/affine/affine_generic.o

C_DEPS += \
./mtkernel_3/lib/nnablart/functions/implements/neural_network/affine/affine.d \
./mtkernel_3/lib/nnablart/functions/implements/neural_network/affine/affine_fixed16.d \
./mtkernel_3/lib/nnablart/functions/implements/neural_network/affine/affine_fixed8.d \
./mtkernel_3/lib/nnablart/functions/implements/neural_network/affine/affine_generic.d

mtkernel_3/lib/nnablart/functions/implements/neural_network/affine/%.o: ../lib/nnabla_c_runtime/src/functions/implements/neural_network/affine/%.c
	@echo 'Building file: $<'
	$(GCC) $(CFLAGS) -D$(TARGET) $(INCPATH) -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '
