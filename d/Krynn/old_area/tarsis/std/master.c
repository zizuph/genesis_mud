/* Master file to store whether Tarsis is currently overrun by dracs
 * or not.
 */

#pragma no_inherit
#pragma no_clone

#define SAVE_FILE "/d/Krynn/tarsis/std/master"

inherit "/std/object";

int attack = 0;

void
create_object()
{
    seteuid(getuid(this_object()));
    restore_object(SAVE_FILE);
}

/* query function. Call this function to see if there is currently an
 * attack. Returns 0 if everything is normal, 1 if there is an attack.
 */
int
query_attack()
{
    return attack;
}

/* */
int
toggle_attack()
{
    attack = !attack;
    seteuid(getuid(this_object()));
    save_object(SAVE_FILE);
}

/* call this function from externally to start the drac invasion */
int
start_attack()
{
    attack = 0;
    toggle_attack();
}

/* and call this function from externally to end it again */
int
end_attack()
{
    attack = 1;
    toggle_attack();
}
