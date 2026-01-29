/*
 * macros.h
 *
 * This file includes shortcuts to frequently used but
 * lengthy pieces of code. Rather than including code
 * into files, these macros are shortcuts to the actual
 * functions in a global object, which is
 * /d/Khalakhor/sys/global/macros.c
 *
 * Khail - June 21/97
 */
#ifndef KHALAKHOR_MACROS
#define KHALAKHOR_MACROS

#define MACROS_FILE "/d/Khalakhor/sys/global/macros"

/*
 * Macro name : CAN_ATTACK
 * Description: Decides of ob1 can attack ob2.
 * Arguments  : x - Object pointer to attacker.
 *              y - Object pointer to target.
 *              z - True if default reasons for
 *                  failure wanted.
 * Returns    : mixed.
 *              0 - Ob1 can attack ob2.
 *              1 to 11 - Various flags representing
 *                        the reason for attack failure.
 *                        Read the function header in
 *                        macros.c for details.
 *              ({fail_flag, fail_message}) - Array produced
 *                        by verbose mode. Fail flag is
 *                        again integers 1 to 11. The fail
 *                        message is a string giving a
 *                        default reason why the attack
 *                        fails.
 */
#define CAN_ATTACK(x,y,z) MACROS_FILE->can_attack(x,y,z)

#endif