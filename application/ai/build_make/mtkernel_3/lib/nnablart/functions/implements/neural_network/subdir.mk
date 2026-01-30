################################################################################
# micro T-Kernel 3.00.03  makefile
################################################################################

OBJS += \
./mtkernel_3/lib/nnablart/functions/implements/neural_network/average_pooling.o \
./mtkernel_3/lib/nnablart/functions/implements/neural_network/deconvolution.o \
./mtkernel_3/lib/nnablart/functions/implements/neural_network/max_pooling.o \
./mtkernel_3/lib/nnablart/functions/implements/neural_network/pooling.o \
./mtkernel_3/lib/nnablart/functions/implements/neural_network/sum_pooling.o \
./mtkernel_3/lib/nnablart/functions/implements/neural_network/unpooling.o

C_DEPS += \
./mtkernel_3/lib/nnablart/functions/implements/neural_network/average_pooling.d \
./mtkernel_3/lib/nnablart/functions/implements/neural_network/deconvolution.d \
./mtkernel_3/lib/nnablart/functions/implements/neural_network/max_pooling.d \
./mtkernel_3/lib/nnablart/functions/implements/neural_network/pooling.d \
./mtkernel_3/lib/nnablart/functions/implements/neural_network/sum_pooling.d \
./mtkernel_3/lib/nnablart/functions/implements/neural_network/unpooling.d

mtkernel_3/lib/nnablart/functions/implements/neural_network/%.o: ../lib/nnabla_c_runtime/src/functions/implements/neural_network/%.c
	@echo 'Building file: $<'
	$(GCC) $(CFLAGS) -D$(TARGET) $(INCPATH) -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

include mtkernel_3/lib/nnablart/functions/implements/neural_network/affine/subdir.mk
include mtkernel_3/lib/nnablart/functions/implements/neural_network/convolution/subdir.mk
