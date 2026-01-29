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


void
create_khalakhor_human()
{
	
	set_name(({guardname()}));
	add_name(({"guard"}));
	set_adj(({emotelook(),physlook()}));
	set_long("This is a tough-looking barbaric guard, who stands as a"
		+"silent sentry, equipped with the training and experience "
	    +"to convey his feeling of chaos and bloodthirst to his unlucky "
		+"foes. He looks absolutely barbaric, and doesn't seem to want "
		+"anything more than to personally bash your head in. He is wearing "
		+"the read and black colours of the clan Baran, and his kilt  "
		+"displays his rank being that of a footman of the clan.\n");
			
    set_gender(G_MALE);
    set_stats(({ 100, 100, 100, 100, 100, 120 }));
    
	set_pick_up_team(({"guard"}));
	
    set_alignment(-500);

    set_skill(SS_WEP_SWORD, 75);
    set_skill(SS_WEP_CLUB, 75);
    set_skill(SS_WEP_POLEARM, 75);
    set_skill(SS_PARRY, 60);
    set_skill(SS_DEFENCE, 60);
	set_skill(SS_BLIND_COMBAT, 40);
    
    // Emotes with 50sec interval
    set_act_time(50);
    add_act("emote dutifully cleans his armours, removing "
		+"blood and gore from sight and mind.");
    add_act("emote straightens up the room, fixing the "
		+"tent stakes, shields resting against the tent, "
		+"and other equipment that has fallen over recently.");
    add_act("emote adjusts his kilt, greaves, and bracers.");
	add_act("emote describes the rough life accompanying "
		+"the warriors of the clan Baran.");
    
    // Combat emotes with 8sec interval
    set_cact_time(8);
    add_cact("shout Annoying fiend! It's to the death if you're lucky weak-armed joke of a warrior!");
    add_cact("emote growls menacingly.");
    add_cact("asay dark So you call yourself a warrior? I'll beat you until "
        +"you can't even recognize yourself anymore!");
	add_cact("emote looks at the wounds he caused darkly and with pride.");
		
    add_prop(OBJ_I_RES_POISON, 10);
    add_prop(OBJ_I_RES_FIRE, -10);
    
    add_prop(NPC_I_NO_RUN_AWAY, 1);
    
    equip("/w/stark/celtcamp/kguard_items/Csword");
	equip("/w/stark/celtcamp/kguard_items/Cshield");
	equip("/w/stark/celtcamp/kguard_items/Chelm");
	equip("/w/stark/celtcamp/kguard_items/Cgreaves");
	equip("/w/stark/celtcamp/kguard_items/Ckilt");
	equip("/w/stark/celtcamp/kguard_items/Cbracers");
	
}

int
special_attack(object enemy)
{
    int     attacktype,
            pen,
            att,
            wloc;

    mixed   hitres;
    
    object *shield;

    string *hitloc,
           *attack,
            how,
            weapon;

    shield = filter(query_armour(-1), &operator(==)(, A_SHIELD) 
             @ &->query_at());

    if (!sizeof(shield))
        return 0;

    attacktype = random(5);

    hitloc = ({"left arm","right arm","body","left leg","right leg"});

    attack = ({"swipe","swing"});

    weapon = shield[0]->query_short();

    if (attacktype == 1)
    {
        pen = 530;
        hitres = enemy->hit_me(pen, W_BLUDGEON, this_object(), -1);

        wloc = random(5);
        att  = random(2);

        if (hitres[0] <= 0)
            how = "his " + weapon + " narrowly missing";
        if(hitres[0] > 0)
            how = "his " + weapon + " slightly bruising";
        if(hitres[0] > 10)
            how = "his " + weapon + " badly cracking accross";
        if(hitres[0] > 20)
            how = "his " +weapon+ " horribly smashing";
        if (hitres[0] > 40)
            how = "his " + weapon + " cracking the bones underneath";
        if (hitres[0] > 60)
            how = "his " + weapon + " lethally pounding the life out of";

        enemy->catch_msg(QCTNAME(this_object()) + 
            " executes a well-trained " +attack[att]
            + " at you, " + how + " your " + hitloc[wloc] + ".\n");

        tell_room(environment(this_object()), QCTNAME(this_object()) +
            " takes a mighty " +attack[att]+ 
            " at " +QCTNAME(enemy) + ", " +how+ " " +POSSESSIVE(enemy)
            + " " + hitloc[wloc] + ".\n", ({ enemy, this_object() }));

        if (enemy->query_hp() <= 0)
        {
            enemy->do_die(this_object());
        }

        return 1;
    }

    return 0;
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
    physlooks = ({"tall", "blue-eyed", "grey-eyed", "brown-eyed", "imposing",
        "black-haired", "brown-haired", "grey-haired", "green-eyed", "bald",
        "long-legged", "lithe", "muscular", "slender", "strong", "massive",
        "burly", "bearded", "clean-shaven", "strong-armed", "barrel-chested", 
        "lean", "large", "thick-armed", "sturdy"});
    return physlooks[random(sizeof(physlooks))];
}

string
emotelook()
{
    string *emotelooks;
    emotelooks = ({"stern", "fierce", "stoic", "malevolent", "untrustworthy",
        "articulate", "frowning", "grim", "experienced", "deadly", "dangerous",
        "wary", "alert", "rash", "silent", "watchful", "fierce",
        "formidable", "unsympathetic", "greedy", "arrogant", "unreliable",
		"handsome", "cruel", "ugly"});
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
