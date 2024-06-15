# Architecture
Multi-core CPU package, with 64 bit address bus and 32 bit data bus. Memory mapped I/O with the ability to detect and swap I/O using exchangable packages.

## Registers
### General Purpose Registers
The general purpose registers for this architecture are denoted as r0 through r7, and are 32 bits wide. These registers have no special, or secondary, purpose within the architecture. Each of these registers has two shadow registers denoted with h0 through h7, and l0 through l7; shadow registers prefixed with h indicate the high short value in the full register, and shadow registers prefixed with l indicate the low short value in the full registers. Only general purpose registers have this specific special h and l shadow registers configuration, the special purpose registers may have shadow registers but aren't guaranteed.

### Special Purpose Registers
| register | bits | purpose |
|----------|------|---------|
| ip | 64 bits | Points to the next instruction to be executed, cannot be directly modified except through special flow instructions. |
| stp | 64 bits | Points to the next stack position that will be used. |
| sfp | 64 bits | Points to the current stack frame, used for debugging and quick stack frame discard. |
| flags | 64 bits | A bitset of CPU core specific flags and state information that assists in flow control, and CPU operation. |

#### IP Register
Points to the next instruction to be executed, cannot be directly modified except through special flow instructions.

#### STP Register
Points to the next stack position that will be used.

#### SFP Register
Points to the current stack frame, used for debugging and quick stack frame discard.

#### Flags Register
A bitset of CPU core specific flags and state information that assists in flow control, and CPU operation. Cannot be directly accessed, requires a stack operation to indirectly access it.

| flag | bit index | bit count | purpose |
|------|-----------|-----------|---------|
| ZF   | 0 | 1 | Zero flag, usually used to indicate last instruction resulted in a zero. |
| CF   | 1 | 1 | Carry flag, usually used to indicate last instruction resulted in a carry. |
| SF   | 2 | 1 | Sign flag, usually used to indicate last instruction resulted in a negative number, or highest bit set. |
