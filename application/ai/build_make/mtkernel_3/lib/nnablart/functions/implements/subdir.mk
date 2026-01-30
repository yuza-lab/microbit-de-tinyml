################################################################################
# micro T-Kernel 3.00.03  makefile
################################################################################

include mtkernel_3/lib/nnablart/functions/implements/activation/subdir.mk
include mtkernel_3/lib/nnablart/functions/implements/arithmetic/subdir.mk
include mtkernel_3/lib/nnablart/functions/implements/array/subdir.mk
include mtkernel_3/lib/nnablart/functions/implements/logical/subdir.mk
include mtkernel_3/lib/nnablart/functions/implements/math/subdir.mk
include mtkernel_3/lib/nnablart/functions/implements/neural_network/subdir.mk
include mtkernel_3/lib/nnablart/functions/implements/normalization/subdir.mk
include mtkernel_3/lib/nnablart/functions/implements/quantization/subdir.mk
include mtkernel_3/lib/nnablart/functions/implements/reduction/subdir.mk
include mtkernel_3/lib/nnablart/functions/implements/stochasticity/subdir.mk

OBJS += \
./mtkernel_3/lib/nnablart/functions/implements/unimplemented.o 

C_DEPS += \
./mtkernel_3/lib/nnablart/functions/implements/unimplemented.d 

mtkernel_3/lib/nnablart/functions/implements/%.o: ../lib/nnabla_c_runtime/src/functions/implements/%.c
	@echo 'Building file: $<'
	$(GCC) $(CFLAGS) -D$(TARGET) $(INCPATH) -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '
