/* intro.c: Inheritable to allow intro: Serpine, August 98. */

#pragma strict_types
#pragma save_binary

int has_introduced=0;


/* Function name: remove_intro & introduce me
 * Description:   Used by add_introduced to reset & intro respectively
 */
void remove_intro() { has_introduced=0; }
public void introduce_me(string person) { command("introduce myself"); }


/* Function name: add_introduced
 * Description:   Intro when introduced to if not done lately.
 * Arguments:     person - Person who introduced to me.
 */
void
add_introduced(string person)
{
    if(!has_introduced)
        {
            set_alarm(6.0, 0.0, &introduce_me(person));
            has_introduced=1;
            set_alarm(30.0, 0.0, "remove_intro");
        }
}
