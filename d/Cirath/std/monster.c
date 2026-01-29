/* monster.c: The Cirath replacement for /std/monster.
 *     Largely based on the Krynn version, with other odd
 *     bits inserted/removed here and there.
 *                           -- Serpine, 2/23/96.
 *
 * WARNING: Don't mess with this file, its going to be
 *          used all over the place in this domain.
 *--------------------------------------------------------
 */
 
#pragma strict_types
#pragma save_binary
 
inherit "/std/monster";
#include "defs.h"
 
string assist_cry="";
string speak_string="";
int has_introduced=0;
 
 
/* Function name: set_assist_cry & query_assist_cry
 * Description:   These functions set and query the current thing said
 *                by someone when they move to defend a teammate.
 * Arguments:     cry - what is to be said
 */
void set_assist_cry(string cry) { assist_cry = cry; }
string return_assist_cry() { return assist_cry; }
 
 
/* Function name: set_speak & return_speak
 * Description:   These functions set and query the current thing said
 *                by someone when they are spoken to.
 * Arguments:     speach - what is to be said
 */
void set_speak(string speech) { speak_string = speech; }
string return_speak() { return speak_string; }
 
 
/* Function name: create_monster & init_living
 * Description:   The standard create and init_living, do ::create_monster()
 *                and ::init_living in them respectively to use them
 */
void
create_monster()
{
    ::create_monster();
    set_assist_cry("How dare you attack my associate!");
    set_default_answer(VBFC_ME("unknown_sorry_response"));
}
void
init_living()
{
    ::init_living();
    add_action("do_speak", "speak");
}

/*
  Name: unknown_sorry_response
  Desc: Default statment about having no idea.
  Args:
  Returns:
*/
public string
unknown_sorry_response()
{
    command("say Sorry. I'm not sure what you want to know.");
    return "";
}
 
/* Function name: do_speak
 * Description:   This function makes the monster respond to speak.
 * Arguments:     string - who the player wants to speak to
 */
int
do_speak(string who)
{
    object spoken_to, *obj;
    object speaker = this_player();
 
    if (!strlen(who))
    {
        speaker->catch_msg("Perhaps speak to someone specific?\n");
        return 1;
    }
    
    if(!parse_command(who, ENV(speaker), "[to] / [with] [the] %l", obj))
    {
        speaker->catch_msg("Just who do you want to speak with?\n");
        return 1;
    }
    spoken_to = obj [1];
 
    if(((spoken_to->return_speak())=="") || ((spoken_to->return_speak())==0))
    {
        speaker->catch_msg("You give it a shot, but " + QCTNAME(spoken_to) 
                          +" isn't much of a speaker.\n");
        say(QCTNAME(speaker) + " starts uselessly ranting about "
               +"various matters to " + QCTNAME(spoken_to) + ".\n");
        return 1;
    }
 
    speaker->catch_msg("You discuss many matters with " + QCTNAME(spoken_to)
             + " till finally " + HE_SHE(spoken_to) + " says:\n -- "
             + (spoken_to->return_speak()) +"\n");
    say(QCTNAME(speaker) + " and " + QCTNAME(spoken_to)
       +" engage in a long, private conversation.\n");
    return 1;
}
 
 
/* Function name: attacked_by
 * Description:   This function is called when somebody attacks this object
 * Arguments:     ob - The attacker
 */
void
attacked_by(object ob)
{
    object *arr;
    int i;
 
    ::attacked_by(ob);
 
    arr = (object *)query_team_others();
    for (i = 0; i < sizeof(arr); i++)
        arr[i]->notify_ob_attacked_me(this_object(), ob);    
}
 
 
/* Function name: notify_ob_attacked_me
 * Description:   This is called when someone attacks a team member of mine
 * Arguments:     friend - My team mate,   attacker - The attacker
 */
void
notify_ob_attacked_me(object friend, object attacker)
{
    if (query_attack())
        return;
 
    if (random(10))
        call_out("help_friend", 1, attacker);
}
 
 
/* Function name: help_friend
 * Description:   Help my friends by attacking their attacker
 * Arguments:     attacker - The person who attacked my friend
 */
void
help_friend(object ob)
{
    if (ob && !query_attack() && present(ob, environment()))
    {
        command("' "+(return_assist_cry()));
        command("kill " + lower_case(ob->query_real_name()));
    }
}
 
 
/* Function name: add_introduced
 * Description:   Intro when introduced to if not done lately.
 *                Will only function if I have a title.
 * Arguments:     person - Person who introduced to me.
 */
void
add_introduced(string person)
{
    if((this_object()->query_title())=="") return;
    if(!has_introduced)
        {
            set_alarm(6.0, 0.0, "introduce_me");
            has_introduced=1;
            set_alarm(30.0, 0.0, "remove_intro");
        }
}
 
/* Function name: remove_intro & introduce me
 * Description:   Used by add_introduced to reset & intro respectively
 */
void remove_intro() { has_introduced=0; }
void introduce_me() { command("introduce myself"); }
 
 
/* Function name: make_cash
 * Description:   Clone some money into the critter.
 * Arguments:     how_much = Amount to make.
 *                type = "copper", "silver", "gold", "platinum"
 */
void
make_cash(int how_much, string type)
{
    object cash;
 
    seteuid(getuid(this_object()));
 
    cash=clone_object("/std/coins");
    cash->set_heap_size(how_much);
    cash->set_coin_type(type);
    cash->move(this_object(),1);
}
