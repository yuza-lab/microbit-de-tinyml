################################################################################
# micro T-Kernel 3.00.03  makefile
################################################################################

OBJS += \
./mtkernel_3/lib/nnablart/functions/implements/array/concatenate.o \
./mtkernel_3/lib/nnablart/functions/implements/array/flip.o \
./mtkernel_3/lib/nnablart/functions/implements/array/matrix_diag.o \
./mtkernel_3/lib/nnablart/functions/implements/array/matrix_diag_part.o \
./mtkernel_3/lib/nnablart/functions/implements/array/pad.o \
./mtkernel_3/lib/nnablart/functions/implements/array/reshape.o \
./mtkernel_3/lib/nnablart/functions/implements/array/shift.o \
./mtkernel_3/lib/nnablart/functions/implements/array/slice.o \
./mtkernel_3/lib/nnablart/functions/implements/array/split.o \
./mtkernel_3/lib/nnablart/functions/implements/array/stack.o \
./mtkernel_3/lib/nnablart/functions/implements/array/transpose.o

C_DEPS += \
./mtkernel_3/lib/nnablart/functions/implements/array/concatenate.d \
./mtkernel_3/lib/nnablart/functions/implements/array/flip.d \
./mtkernel_3/lib/nnablart/functions/implements/array/matrix_diag.d \
./mtkernel_3/lib/nnablart/functions/implements/array/matrix_diag_part.d \
./mtkernel_3/lib/nnablart/functions/implements/array/pad.d \
./mtkernel_3/lib/nnablart/functions/implements/array/reshape.d \
./mtkernel_3/lib/nnablart/functions/implements/array/shift.d \
./mtkernel_3/lib/nnablart/functions/implements/array/slice.d \
./mtkernel_3/lib/nnablart/functions/implements/array/split.d \
./mtkernel_3/lib/nnablart/functions/implements/array/stack.d \
./mtkernel_3/lib/nnablart/functions/implements/array/transpose.d

mtkernel_3/lib/nnablart/functions/implements/array/%.o: ../lib/nnabla_c_runtime/src/functions/implements/array/%.c
	@echo 'Building file: $<'
	$(GCC) $(CFLAGS) -D$(TARGET) $(INCPATH) -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '
