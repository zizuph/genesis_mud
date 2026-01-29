/*
 * smith_rack_shadow.c
 *
 * This shadow is added to weapons placed in the bladesmith's weapons
 * rack to prevent them from being taken until paid for.
 *
 * Khail - May 11/97
 */
#pragma strict_types

inherit "/std/shadow";

/*
 * Function name: move (SHADOWED)
 * Description  : Called to move this object to a new environment.
 * Arguments    : See 'sman /std/object move'.
 * Returns      : See 'sman /std/object move'.
 */
varargs public int
move(mixed dest, mixed subloc)
{
    write("The " + shadow_who->short() + " cannot be taken from " +
        "the " + environment(shadow_who)->short() + " until you " +
        "pay for it and the smith unlocks it.\n");
    return 7;
}