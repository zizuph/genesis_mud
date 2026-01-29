/* 
 *  The half-elf/half-human tender 
 *  to the great loom of strands
 *  at the nexus of the treetop
 *  fortress of the Elven
 *  Archers of Ansalon
 *
 *  Vitwitch 12/2020
 */
#include <stdproperties.h>
#include <wa_types.h>
#include <ss_types.h>
#include <macros.h>
#include <composite.h>
#include "/d/Krynn/common/defs.h"
#include <math.h>
#include <filter_funs.h>

#define ELFNAME "quenexa"
#define ELFCAMP "/d/Krynn/qualinesti/elf_camp/"
#define FOREST "/d/Krynn/qualinesti/forest/"

inherit M_FILE  // ...a.k.a. "/d/Krynn/std/monster";


mixed
count_race_align(string locn, mapping oldcount)
{

    object *inv, *ppl, target;
    int nppl, i;
    string str, align;
    mapping newcount;
    mixed ind, val;

    ind = m_indices(oldcount);
    val = m_values(oldcount);

    newcount = mkmapping(ind, val);

    target = find_object(locn);
    inv = all_inventory(target);
    ppl = FILTER_LIVE(inv);

    nppl = sizeof(ppl);

    for ( i=0;i<nppl;i++ )
    {
        align = "g";
        if ( ppl[i]->query_alignment() < -100 ) align = "e";
        str = sprintf("%s_%s",ppl[i]->query_race(),align);
        newcount[ str ]++;  
    }

    return newcount;
}


string
num_descrip(int n)
{
    string descriptor;

    switch (n)
    {
    case 0:
        descriptor = "no";
        break;

    case 1..2:
        descriptor = "one or two";
        break;

    case 3..5:
        descriptor = "a handful of";
        break;

    case 6..10:
        descriptor = "a company of";
        break;

    case 11..20:
        descriptor = "a small army of";
        break;

    default:
        descriptor = "a large army of";
    }

    return descriptor;
}

int
report_race_align( string *race_evil,
                   string *race_good,
                   string *race_animal,
                   string *racee_sound,
                   string *raceg_sound,
                   string *racea_sound,
                   mapping racecount)
{

    int n, nr, ir, nevil, ngood, nanimal;
    string report;
    string sounds = " ~~ ";

    command( "say It is well that you ask! Let me consult my tablet...\n" );

    // baddies

    nr = sizeof(race_evil);
    report = "";

    for ( nevil=0,ir=0;ir<nr;ir++ )
    {
        n = racecount[race_evil[ir]];
        nevil += n;
        if ( n!=0 ) report = sprintf("%s\n %s %s %s",
                 report,sounds,num_descrip(n),racee_sound[ir]);
    }

    if ( nevil != 0 ) 
        command("say The forest of Qualinesti is threatened by..." + report + "\n");

    // animals

    nr = sizeof(race_animal);
    report = "";

    for ( nanimal=0,ir=0;ir<nr;ir++ )
    {
        n = racecount[race_animal[ir]];
        nanimal += n;
        if ( n!=0 ) report = sprintf("%s\n %s %s %s",
                 report,sounds,num_descrip(n),racea_sound[ir]);
    }

    if ( nanimal != 0 ) 
      command("say The forest wilderness is currently home to..." + report + "\n");


    // goodies

    nr = sizeof(race_good);
    report = "";

    for ( ngood=0,ir=0;ir<nr;ir++ )
    {
        n = racecount[race_good[ir]];
        ngood += n;
        if ( n!=0 ) report = sprintf("%s\n %s %s %s",
                report,sounds,num_descrip(n),raceg_sound[ir]);
    }

    if ( ngood != 0 ) 
     command("say Our great forest Realm is ever grateful to host.." + report + "\n");

    return 1;
}


int
do_monitor()
{
    int i;
    string str;
    string *race_evil, *race_good, *race_animal, *race_all;
    string *racee_sound, *raceg_sound, *racea_sound;
    string report;
    mapping racecount;

    race_evil = ({ "goblin_e", "human_e", "dwarf_e", "hobbit_e", "gnome_e", "elf_e" }); 
    racee_sound = ({ "evil goblins skulking where they should not be...",
                     "dark-spirited humans striding about arrogantly...",
                     "nefarious dwarves crushing innocent flora and fauna...",
                     "grim halflings of ill-repute sneaking about...",
                     "gnomes of dark-contrapting intent doing bad things...",
                     "elves, fallen from the light, scratching about in the dark..." });

    race_good = ({ "goblin_g", "human_g", "dwarf_g", "hobbit_g", "gnome_g", "elf_g" }); 
    raceg_sound = ({ "good-hearted goblins wandering aimlessly about...",
                     "humans of good spirit and bold steps...",
                     "honourable dwarves marching about in good order...",
                     "halflings of a jolly disposition pitter-pattering around...",
                     "gnomes of a good-natured bent examining the forest...",
                     "elves, true-hearted and of noble intent..." });

    race_animal = ({"wolf_g", "rabbit_g", "hare_g", "stag_g", "deer_g", 
                       "fox_g", "dog_g", "squirrel_g"});
    racea_sound = ({ "wolves...",
                     "rabbits...",
                     "hares...",
                     "stags...",
                     "other deer...",
                     "foxes...",
                     "dogs...",
                     "squirrels..." });

    race_all = race_evil[0..5] + race_good[0..5] + race_animal[0..7];

    racecount = mkmapping( race_all, ({0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0}) );

    for (i=1;i<23;i++)
    {
        str = sprintf("%s%s%d", ELFCAMP, "camp", i);
        racecount = count_race_align(str,racecount);
    }
    for (i=1;i<2;i++)
    {
        str = sprintf("%s%s%d", ELFCAMP, "ambush", i);
        racecount = count_race_align(str,racecount);
    }
    for (i=1;i<3;i++)
    {
        str = sprintf("%s%s%d", ELFCAMP, "oak", i);
        racecount = count_race_align(str,racecount);
    }
    for (i=0;i<55;i++)
    {
        str = sprintf("%s%s%d", FOREST, "forest", i);
        racecount = count_race_align(str,racecount);
    }

    report_race_align(race_evil,race_good,race_animal,
                      racee_sound,raceg_sound,racea_sound,
                      racecount);

    return 1;
}

string
wax_tablet()
{
    return "The half-elf notices you examining her wax tablet...and mutters about her list\n";
}

string
adjust_shaft()
{
    tell_room(E(TO),
     "The half-elf changes the angle of one of the strand-bearing arrow shafts"+
     " in the great loom.\n");
    return "";
}

string
tension_strand()
{
    tell_room(E(TO),
     "The half-elf changes the tension on one of the silken"+
     " strands running through the great loom.\n");
    return "";
}

string
ponder_a_bit()
{
    tell_room(E(TO),
     "The half-elf pauses in thought to consider adjustments to the great"+
     " loom -- to improve the reception of faint sounds from far away.\n");
    return "";
}


void
ask_for_report()
{
    set_alarm(3.0,0.0,&do_monitor());
}


void
create_krynn_monster()
{
    set_title("Half-Elven Ear of Qualinesti");

    set_living_name( ELFNAME );
    set_name( ELFNAME );
    set_race_name("elf");
    add_name( "half-elf" );

    set_adj("restless");
    set_adj("finicky");
    set_adj("quick");

    set_gender(1);  // female
    set_alignment(800);
    set_knight_prestige(-300);

    add_prop(NPC_I_NO_LOOKS, 1);
    add_prop(CONT_I_HEIGHT, 95);
    add_prop(CONT_I_WEIGHT, 12500);

    set_long("Before you, a venerable she-elf of diminutive" +
        " stature rushes all over the great loom of strands"+
        " that dominates the room -- intently tuning and listening,"+
        " retuning and listening again -- while whispering to herself."+
        " Her obsession with such a contrapted object invites a closer"+
        " inspection of her features, revealing the truth. Human"+
        " blood is mixed with the elvish in her long ancestry."+
        " As she listens to the"+
        " faintly humming loom, she makes a tally on a wax tablet.\n");

    set_short("elf with a curious cast to her features");
    set_pshort("elves with curious casts to their features");

    add_item(({"tablet","wax tablet"}),"@@wax_tablet");

    add_ask(({"list","tablet","tally","report","movements","movement"}), "@@ask_for_report",1);

    set_default_answer("Nods at your question..."+
     " but continues obsessively listening and tallying.\n",0);

    set_act_time(15);
    add_act("@@adjust_shaft");
    add_act("@@tension_strand");
    add_act("@@ponder_a_bit");

    trig_new("%w 'introduces' %s","react_to_intro");

    trig_new("%w 'says' %s","react_to_saying");
    trig_new("%w 'shouts' %s","react_to_saying");
    trig_new("%w 'grates' %s","react_to_saying");
    trig_new("%w 'mumbles' %s","react_to_saying");
    trig_new("%w 'hisses' %s","react_to_saying");
    trig_new("%w 'thunders' %s","react_to_saying");
    trig_new("%w 'sings' %s","react_to_saying");
    trig_new("%w 'whispers' %s","react_to_saying");
    trig_new("%w 'chirps' %s","react_to_saying");
    trig_new("%w 'bellows' %s","react_to_saying");

    set_stats(({90,160,400,400,400,200}));
    set_hp(query_max_hp());

    add_prop(OBJ_M_NO_ATTACK,"Umm... no, You " +
      "do not have the self-discipline to dare!\n");

    add_prop(LIVE_I_ATTACK_THIEF, 0);
    add_prop(OBJ_I_NO_MAGIC, 1);
    add_prop(LIVE_I_SEE_DARK, 2);
    add_prop(OBJ_I_NO_DROP, 1);
    add_prop(OBJ_I_NO_GIVE, 1);
    add_prop(OBJ_I_NO_GET, 1);
    add_prop(OBJ_I_NO_STEAL, 1);
    add_prop(OBJ_I_NO_TELEPORT, 1);
    add_prop(OBJ_I_NO_BUY, 1);
    add_prop(OBJ_I_NO_SELL, 1);
    add_prop(NPC_I_NO_RUN_AWAY,1);
    add_prop(NPC_M_NO_ACCEPT_GIVE,1);
    add_prop(NPC_I_NO_RUN_AWAY, 1);

    seteuid(getuid(TO));
}

void
react_to_asking()
{
    write("Nods at your question while obsessively listening and tallying.\n");
    return;
}

void
intro_me(string who)
{
    who = L(who);
    if (P(who,E(TO)))
    {
        command("introduce myself");
    }
}

void
react_to_intro(string who,string garbage)
{
    set_alarm(1.0,0.0,"intro_me",who);
}

void
react_to_saying(string who,string garbage)
{
    write( "The half-elf "+
         "pointedly puts a long finger to her lips, "+
         "shushing you to silence!\n");
}

void
init_living()
{
    ::init_living();
    add_action("do_monitor","monitor");
}
