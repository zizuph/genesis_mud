inherit "/d/Khalakhor/std/npc/human";
inherit "/d/Shire/common/auto_teaming";

#include <const.h>
#include <stdproperties.h>
#include <ss_types.h>
#include <macros.h>
#include <wa_types.h>
#include "/d/Gondor/defs.h"



string physlook();
string emotelook();
string guardname();

string build();
string beard();
string age();

string
build()
{
    string *builds;
    builds = ({"hulking", "weak-armed", "well-built", "muscular"});
    return builds[random(sizeof(builds))];
}

string
beard()
{
    string *beards;
    beards = ({"stubbled beard", "shadow of a beard",
	      "neatly trimmed beard","big, scruffy beard"});
    return beards[random(sizeof(beards))];
}

string
age()
{
    string *ages;
    ages = ({"an aged", "an old", "a middle-aged", "a youthful",
        "a young", "an adolescent", "an elder","a matured"});
    return ages[random(sizeof(ages))];
}


void
create_khalakhor_human()
{
	
	set_name(({guardname()}));
	add_name(({"trainee"}));
	set_title("the applicant to the Clan Baran");
	set_adj(({emotelook(),physlook()}));
	set_long("This is "+age()+" trainee of the Clan Barn and he "
		    +"is sporting "+beard()+". He is currently focused on "
		    +"honing the skills and traits that will allow him "
		    +"to prosper as a "+build()+" warrior.\n");
			
    set_gender(G_MALE);
	
    set_stats(({ 25, 25, 25, 25, 25, 50}));
    
	set_pick_up_team(({"trainee"}));
	
    set_alignment(-1200);

    set_skill(SS_WEP_SWORD, 25);
    set_skill(SS_PARRY, 25);
    set_skill(SS_DEFENCE, 25);
    
    // Emotes with 25sec interval
    set_act_time(random(25));
	
	add_act("emote trims his "+beard()+" dutifully");
	
	add_act("emote dutifully cleans his armours, futilly "
		   +"trying to get the praise of his superiors.");
	
    add_act("emote straightens up the training site, "
		   +"picking up swords and shields, as well as "
		   +"reparing and replacing the practice dummies.");
	
	add_act("emote takes a moment to work on his swordplay "
		   +"alone, honing in on creating an instrument of "
		   +"death out of his blade.");
	
	add_act("emote gestures to another trainee, offering "
		   +"to spar in order for some additional practice.");
    
    // Combat emotes with 8sec interval
    set_cact_time(random(8));
    add_cact("shout This is exactly the triumph I need to gain entry into the clan!");
    add_cact("emote readjusts his combat stance, attempting to turn the tide of the battle.");
	add_cact("emote turns to focus on pressing his attacks forward, focusing on offense.");
	add_cact("emote roars with fury! He begins to focus on pressing his attacks.");
		
    add_prop(OBJ_I_RES_POISON, 10);
    add_prop(OBJ_I_RES_FIRE, -10);
    
    add_prop(NPC_I_NO_RUN_AWAY, 1);
    
    
	equip("/d/Khalakhor/se_speir/camp/kguard_items/Cshield");
	equip("/d/Khalakhor/se_speir/camp/kguard_items/Chelm");
	equip("/d/Khalakhor/se_speir/camp/kguard_items/Cgreaves");
	equip("/d/Khalakhor/se_speir/camp/kguard_items/Ckilt");
	equip("/d/Khalakhor/se_speir/camp/kguard_items/Cbracers");
	
	

	
}


string
guardname()
{
    string *guardname;
    guardname = ({"gillebeart", "raibeart", "ailean", "padruig", "dohmnull",
        "prainnseas", "tomag", "martainn", "ringean", "sachairi", "deistean",
        "bearnard", "frang", "goiridh", "gilleasbuig", "darren", "raghnall",
        "labhrann", "torcadall", "benneit", "micheil", "diarmad", "daidh",
        "comhnall","simidh","colum", "griogair", "oisean", "cathal", "cadwgan",
	    "sandaidh", "dremidydd", "brys", "cadman", "maelog", "ifan", "seth",
		"nest", "treharne", "mabbet", "hewitt", "owens", "powles", "roderick",
		"brickell", "pedr", "dyfed", "dacus", "maddix", "moor", "Alwyn", "luc",
		"peairs", "badham", "Beddoe", "seith", "gwent", "huarwar","glas", "morcan",
	    "tristram", "geddings", "harry", "uilliam", "matho", "fearadhach",
	    "dualtach"});
    return guardname[random(sizeof(guardname))];
}

string
physlook()
{
    string *physlooks;
    physlooks = ({"tall", "blue-eyed", "grey-eyed", "brown-eyed", "short",
        "black-haired", "brown-haired", "grey-haired", "green-eyed", "bald",
        "wild-eyed", "cowardly", "fearful", "fat", "strong", "weak-armed",
        "sweaty", "bearded", "clean-shaven", "strong-armed", "puny", 
        "lean", "skinny", "lean"});
    return physlooks[random(sizeof(physlooks))];
}


string
emotelook()
{
    string *emotelooks;
    emotelooks = ({"uneducated", "unimposing", "terrified", "beastly",
        "dark", "frowning", "grim", "wary", "daydreaming", "rash", "silent", 
        "unsympathetic", "greedy", "arrogant", "unreliable", "evil",
		"plain", "cruel", "ugly"});
    return emotelooks[random(sizeof(emotelooks))];
}

void
init_living()
{
    init_team_pickup();
    ::init_living();
}

void
add_introduced(string str)
{
    if (!interactive(TP) || TP->query_met(query_name()))
        return;

    command("introduce me to " + TP->query_real_name() + "");
}
