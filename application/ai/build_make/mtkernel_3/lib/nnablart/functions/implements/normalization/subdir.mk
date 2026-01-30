################################################################################
# micro T-Kernel 3.00.03  makefile
################################################################################

OBJS += \
./mtkernel_3/lib/nnablart/functions/implements/normalization/batch_normalization.o \
./mtkernel_3/lib/nnablart/functions/implements/normalization/mean_subtraction.o

C_DEPS += \
./mtkernel_3/lib/nnablart/functions/implements/normalization/batch_normalization.d \
./mtkernel_3/lib/nnablart/functions/implements/normalization/mean_subtraction.d

mtkernel_3/lib/nnablart/functions/implements/normalization/%.o: ../lib/nnabla_c_runtime/src/functions/implements/normalization/%.c
	@echo 'Building file: $<'
	$(GCC) $(CFLAGS) -D$(TARGET) $(INCPATH) -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '
