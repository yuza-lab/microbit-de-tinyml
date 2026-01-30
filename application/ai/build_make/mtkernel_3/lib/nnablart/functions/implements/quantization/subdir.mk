################################################################################
# micro T-Kernel 3.00.03  makefile
################################################################################

OBJS += \
./mtkernel_3/lib/nnablart/functions/implements/quantization/binary_connect_affine.o \
./mtkernel_3/lib/nnablart/functions/implements/quantization/binary_sigmoid.o \
./mtkernel_3/lib/nnablart/functions/implements/quantization/binary_tanh.o \
./mtkernel_3/lib/nnablart/functions/implements/quantization/binary_weight_affine.o

C_DEPS += \
./mtkernel_3/lib/nnablart/functions/implements/quantization/binary_connect_affine.d \
./mtkernel_3/lib/nnablart/functions/implements/quantization/binary_sigmoid.d \
./mtkernel_3/lib/nnablart/functions/implements/quantization/binary_tanh.d \
./mtkernel_3/lib/nnablart/functions/implements/quantization/binary_weight_affine.d

mtkernel_3/lib/nnablart/functions/implements/quantization/%.o: ../lib/nnabla_c_runtime/src/functions/implements/quantization/%.c
	@echo 'Building file: $<'
	$(GCC) $(CFLAGS) -D$(TARGET) $(INCPATH) -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '
