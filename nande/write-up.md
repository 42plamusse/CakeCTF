# Nande

## Definitions

### NAND gate

A NAND gate is a fundamental building block in digital electronics. It's a type of logic gate that outputs a low signal (0) only if all its inputs are high (1). If any of its inputs are low (0), it outputs a high signal (1). This behavior can be summarized in a truth table:

```table
Input A | Input B | Output
-------------------------
   0    |    0    |   1
   0    |    1    |   1
   1    |    0    |   1
   1    |    1    |   0
```

The term "NAND" is a contraction of "NOT AND", indicating that the function of the NAND gate is the opposite (NOT) of an AND gate, which only outputs a high signal when all its inputs are high. The NAND gate is functionally complete, which means that any other logic function (AND, OR, NOT, etc.) can be constructed from a combination of NAND gates alone. This makes it very important in the design of digital systems.

## Analysis

### Input

- The given program takes a string as an input.
- The ASCII value of each char of the string is converted to a binary number.
- Each of those 8 bits is added into an array commun to all the string's char.

```c
for (char_index = 0; char_index < 0x20; char_index = char_index + 1) {
    for (bit_index = 0; bit_index < 8; bit_index = bit_index + 1) {
        InputSequence[bit_index + char_index * 8] =
            (byte)((int)input[char_index] >> ((byte)bit_index & 0x1f)) & 1;
    }
}
```

### Transformation

Each bit in the sequence is then processed through some combinaision of NAND operations. The process is repeted a large amout of time.

```c
void CIRCUIT(uchar *input_sequence,uchar *output_sequence)

{
  int byte_index;
  int cycle_count;
  
  for (cycle_count = 0; cycle_count < 0x1234; cycle_count = cycle_count + 1) {
    for (byte_index = 0; byte_index < 0xff; byte_index = byte_index + 1) {
      MODULE(input_sequence[byte_index],input_sequence[byte_index + 1],output_sequence + byte_index)
      ;
    }
    MODULE(input_sequence[byte_index],'\x01',output_sequence + byte_index);
    memcpy(input_sequence,output_sequence,0x100);
  }
  return;
}
```

```c
void MODULE(char param_1,char param_2,char *param_3)
{
  char nandResult1;
  char nandResult2;
  char nandResult3;
  
  NAND(param_1,param_2,&nandResult1);
  NAND(param_1,nandResult1,&nandResult2);
  NAND(param_2,nandResult1,&nandResult3);
  NAND(nandResult2,nandResult3,param_3);

  return;
}
```

```table
NAND(b, NAND(a, NAND(a, b))) = c

Input A | Input B | Output C
----------------------------
   0    |    0    |   0
   0    |    1    |   1
   1    |    0    |   1
   1    |    1    |   0
```

This correspond to the truth table of `XOR`.

### Comparison

The output issued by the transformation is then compared with the array `AnswerSequence` stored in memory.

```c
char AnswerSequence[0x100] = {  0x01, 0x01, 0x01, 0x01,
                                0x01, 0x00, 0x00, 0x01,
                                0x01, 0x00, 0x00, 0x01,
                                0x00, 0x00, 0x01, 0x00,
                                0x00, 0x01, 0x01, 0x00,
                                0x00, 0x00, 0x00, 0x01,
                                0x01, 0x01, 0x01, 0x01,
                                [...]};
```
