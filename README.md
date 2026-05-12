Advanced Mathematical Expression Parser (in C)

Developed from scratch in the C programming language, this is an advanced mathematical expression parser and calculator utilizing dynamic memory management (malloc/realloc) and based on Dijkstra's Shunting-Yard algorithm.
This project goes beyond a standard calculator by parsing text-based mathematical expressions (Strings), structuring them according to strict operator precedence, and producing highly accurate floating-point results.

Key Features
- Dynamic Stack Architecture: Instead of fixed-size arrays, data is managed using Dynamic Stack data structures (FloatStack for numbers, CharStack for operators) that automatically expand using realloc when their capacity is reached.

- Operator Precedence (BODMAS/PEMDAS): Addition, subtraction, multiplication, and division operations are correctly ordered and evaluated according to standard mathematical rules.

- Parenthesis Barriers ( ): Fully supports nested parentheses, isolating operations within them and prioritizing their evaluation.

- Right-Associativity: For exponentiation (^) operations, the parser bypasses the standard left-to-right processing and applies the mathematically accurate right-to-left calculation rule (e.g., $2^{3^2}$).

- "Unary Minus" Detective (State Machine): The program employs a real-time state machine (via an expect_unary flag) to seamlessly distinguish whether a minus (-) sign acts as a binary "Subtraction operation" or a unary "Negative sign" for a number. It flawlessly solves complex expressions like -5 * (-3 + 2).

Compilation & Execution
Since the project uses the standard C math library (math.h), the -lm flag must be included when compiling with GCC.

# To compile the project:
gcc main.c stack.c -o calculator -lm

# To run (Linux/Mac):
./calculator

# To run (Windows):
calculator.exe

Example Usage & Outputs

The parser can accurately handle whitespaces, multiple negative signs, and deep parenthesis nesting without failing.

- Example 1: Multiple Unary Minus and Parentheses Test
Infix expression: 3 * (-5) * ( -3 + 2 )
# Background Process Log:
Pushed operator: *
Pushed operator: (
Pushed operator: )
...
Popped operator: +
Popped operator: *

# Expected Result:
Stack elements: 15.00
Stack size: 1

- Example 2: Right-Associativity Exponentiation Test
Infix expression: (2 ^ -3) ^ 2
# Expected Result:
Stack elements: 0.015625
Stack size: 1
# Explanation: First, 2^(-3) = 0.125 is calculated. Then, 0.125^2 = 0.015625 is evaluated.

Developer: Emir Can Özen
