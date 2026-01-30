################################################################################
# micro T-Kernel 3.00.03  makefile
################################################################################

OBJS += \
./mtkernel_3/lib/nnablart/functions/implements/activation/celu.o \
./mtkernel_3/lib/nnablart/functions/implements/activation/crelu.o \
./mtkernel_3/lib/nnablart/functions/implements/activation/elu.o \
./mtkernel_3/lib/nnablart/functions/implements/activation/leakyrelu.o \
./mtkernel_3/lib/nnablart/functions/implements/activation/prelu.o \
./mtkernel_3/lib/nnablart/functions/implements/activation/relu.o \
./mtkernel_3/lib/nnablart/functions/implements/activation/selu.o \
./mtkernel_3/lib/nnablart/functions/implements/activation/sigmoid.o \
./mtkernel_3/lib/nnablart/functions/implements/activation/softmax.o \
./mtkernel_3/lib/nnablart/functions/implements/activation/swish.o \
./mtkernel_3/lib/nnablart/functions/implements/activation/tanh.o

C_DEPS += \
./mtkernel_3/lib/nnablart/functions/implements/activation/celu.d \
./mtkernel_3/lib/nnablart/functions/implements/activation/crelu.d \
./mtkernel_3/lib/nnablart/functions/implements/activation/elu.d \
./mtkernel_3/lib/nnablart/functions/implements/activation/leakyrelu.d \
./mtkernel_3/lib/nnablart/functions/implements/activation/prelu.d \
./mtkernel_3/lib/nnablart/functions/implements/activation/relu.d \
./mtkernel_3/lib/nnablart/functions/implements/activation/selu.d \
./mtkernel_3/lib/nnablart/functions/implements/activation/sigmoid.d \
./mtkernel_3/lib/nnablart/functions/implements/activation/softmax.d \
./mtkernel_3/lib/nnablart/functions/implements/activation/swish.d \
./mtkernel_3/lib/nnablart/functions/implements/activation/tanh.d

mtkernel_3/lib/nnablart/functions/implements/activation/%.o: ../lib/nnabla_c_runtime/src/functions/implements/activation/%.c
	@echo 'Building file: $<'
	$(GCC) $(CFLAGS) -D$(TARGET) $(INCPATH) -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '
