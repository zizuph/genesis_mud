/* counrcpt.c: Council reception room. 'Spot' the cylops will keep
 *     people out of the main chambers till the council is ready to
 *     go on line, at which point he will let some people through.
 *     Of course what the council names him is there own affair,
 *     but I have a think for the name Spot. - Serpine, 4-24-95.
 */
#pragma save_binary

inherit "/d/Cirath/std/room";
#include "defs.h"
#define LCQN(x)  lower_case(x->query_name())

object vote_bucket;
string *revolters;

void
reset_room()
{
return;
    if (QUERY_OVERSEER) return;
    if (!vote_bucket)
    {
        vote_bucket=clone_object(PSION_LOG+"gladvote.c");
        vote_bucket->move(TO);
    }

    vote_bucket->check_over_time();
}

void
create_room()
{
    revolters = ({});
    set_short("hall of the Masters");
    set_long("This vaulted chamber is where the Overseers of the "+
             "Gladiators of Athas can speak with their charges without "+
             "letting them into the private hall to the east. A stain "+
             "darkens the floor, a crimson stain.\n"+
             "Within this place you may 'list masters', or even "+
             "'revolt', though this latter should only be done in the "+
             "case of extreme failure by the Overseers.\n");

   

    INSIDE

    add_exit(PSION_ROOM+"hallway3.c", "up", 0, 1);
    add_exit(PSION_ROOM+"counmain.c", "north", "@@spot_block@@", 1);

    reset_room();
}

void
init()
{
    ::init();
    add_action("do_list", "list");
    add_action("revolt", "revolt"); 
    add_action("regret", "regret");   
}

int
revolt()
{
    object *the_crew;

    NF("Only Gladiators may stage a revolt!\n");
    if (!IS_MEMBER(TP)) return 0;

    NF("You are already revolting as it is!\n");
    if(member_array(LCQN(TP), revolters) > -1) return 0;

    NF("But there is no High Overseer to revolt against!\n");
    if(!QUERY_OVERSEER) return 0;

    revolters = (revolters + ({LCQN(TP)}));
    write("Power to the Gladiators! You are now revolting.\n"+
          "  You may 'regret' this action later.\n");
    say(QCTNAME(TP)+" joins the revolution against the Overseers!\n");

    if (sizeof(revolters) < 20) return 1;

    tell_room(TO, "The Overseers have been overthrown!\n");
    the_crew = call_other(MANAGER, "dump_overseer_array");
    REMOVE_COUN(the_crew[0]);
    revolters = ({});

    return 1;
}

int
regret()
{
    NF("But you aren't revolutionary!\n");
    if(!(member_array(LCQN(TP), revolters) > -1)) return 0;

    revolters = (revolters - ({LCQN(TP)}));
    write ("You are no longer revolutionary.\n");
    say (QCTNAME(TP)+" isn't revolutionary anymore.\n");
    return 1;
}

int
do_list(string str)
{
    string highoverdude, openings, *the_crew;
    string lowoverdud1,lowoverdud2,lowoverdud3,lowoverdud4,lowoverdud5;
    int slots;

    if (!(str == "masters")) return 0;

    the_crew = call_other(MANAGER, "dump_overseer_array");

    highoverdude = "Not filled: Perhaps you should apply?";
    if(the_crew[0]) highoverdude = CAP(the_crew[0]);

    lowoverdud1 = "Not filled. Perhaps you should apply?";
    if(the_crew[1]) lowoverdud1 = CAP(the_crew[1]);

    lowoverdud2 = "Not filled. Perhaps you should apply?";
    if(the_crew[2]) lowoverdud2 = CAP(the_crew[2]);

    lowoverdud3 = "Not filled. Perhaps you should apply?";
    if(the_crew[3]) lowoverdud3 = CAP(the_crew[3]);

    lowoverdud4 = "Not filled. Perhaps you should apply?";
    if(the_crew[4]) lowoverdud4 = CAP(the_crew[4]);

    lowoverdud5 = "Not filled. Perhaps you should apply?";
    if(the_crew[5]) lowoverdud5 = CAP(the_crew[5]);

    write ("\n  The Counsel Members Currently Consist of\n"+
           "  ===========================================================\n"+
           "   High Counseler: "+highoverdude+"\n\n"+
           " Lesser Counselers\n"+
           "            First: "+lowoverdud1+"\n"+
           "           Second: "+lowoverdud2+"\n"+
           "            Third: "+lowoverdud3+"\n"+
           "           Fourth: "+lowoverdud4+"\n"+
           "            Fifth: "+lowoverdud5+"\n"+
           "  -----------------------------------------------------------\n\n");
    return 1;
}
  
int
spot_block()
{
    if((PSION_ROOM+"counmain.c")->query_can_enter_over(lower_case(TP->query_name())))
        return 0;
    TP->catch_msg("Suddenly an area of shadow in the eastern chambers "+
             "seems to take form: A long chitinous shape with two ... no ... "+
             "three sets of gigantic mandibles. Your mind tells you that "+
             "you must fear it: You have no choice in the matter. But as "+
             "you back away the fear subsides and the five yard greyish "+
             "mass again becomes one with the darkness.\n");
    return 1;
}
