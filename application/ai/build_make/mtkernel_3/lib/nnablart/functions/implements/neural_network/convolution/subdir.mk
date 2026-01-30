################################################################################
# micro T-Kernel 3.00.03  makefile
################################################################################

OBJS += \
./mtkernel_3/lib/nnablart/functions/implements/neural_network/convolution/binary_connect_convolution.o \
./mtkernel_3/lib/nnablart/functions/implements/neural_network/convolution/binary_weight_convolution.o \
./mtkernel_3/lib/nnablart/functions/implements/neural_network/convolution/convolution.o \
./mtkernel_3/lib/nnablart/functions/implements/neural_network/convolution/convolution_common.o \
./mtkernel_3/lib/nnablart/functions/implements/neural_network/convolution/convolution_float.o \
./mtkernel_3/lib/nnablart/functions/implements/neural_network/convolution/convolution_generic.o \
./mtkernel_3/lib/nnablart/functions/implements/neural_network/convolution/convolution_int16.o \
./mtkernel_3/lib/nnablart/functions/implements/neural_network/convolution/convolution_int8.o \
./mtkernel_3/lib/nnablart/functions/implements/neural_network/convolution/depthwise_convolution.o

C_DEPS += \
./mtkernel_3/lib/nnablart/functions/implements/neural_network/convolution/binary_connect_convolution.d \
./mtkernel_3/lib/nnablart/functions/implements/neural_network/convolution/binary_weight_convolution.d \
./mtkernel_3/lib/nnablart/functions/implements/neural_network/convolution/convolution.d \
./mtkernel_3/lib/nnablart/functions/implements/neural_network/convolution/convolution_common.d \
./mtkernel_3/lib/nnablart/functions/implements/neural_network/convolution/convolution_float.d \
./mtkernel_3/lib/nnablart/functions/implements/neural_network/convolution/convolution_generic.d \
./mtkernel_3/lib/nnablart/functions/implements/neural_network/convolution/convolution_int16.d \
./mtkernel_3/lib/nnablart/functions/implements/neural_network/convolution/convolution_int8.d \
./mtkernel_3/lib/nnablart/functions/implements/neural_network/convolution/depthwise_convolution.d

mtkernel_3/lib/nnablart/functions/implements/neural_network/convolution/%.o: ../lib/nnabla_c_runtime/src/functions/implements/neural_network/convolution/%.c
	@echo 'Building file: $<'
	$(GCC) $(CFLAGS) -D$(TARGET) $(INCPATH) -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '
