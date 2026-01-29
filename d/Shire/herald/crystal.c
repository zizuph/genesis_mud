/*
 * /d/Shire/herald/book.c
 *
 * The prayer book/spell object for the Heralds of the Valar
 *
 * Totally recoded by Igneous to work within the new Spellsystem.
 *
 * Changed to a crystal shard so not to conflict with other books in the game.
 * Finwe, February 2004
 */
#pragma strict_types
#pragma save_binary

inherit "/d/Genesis/magic/spellcasting";
inherit "/std/object";

// Now we inherit all the spells
inherit "/d/Shire/herald/spells/mel";
inherit "/d/Shire/herald/spells/ramar";
inherit "/d/Shire/herald/spells/palandir";
inherit "/d/Shire/herald/spells/khil";
inherit "/d/Shire/herald/spells/haetir";
inherit "/d/Shire/herald/spells/silme";
inherit "/d/Shire/herald/spells/vanahwesta";
inherit "/d/Shire/herald/spells/ondo";
inherit "/d/Shire/herald/spells/lissinen";
inherit "/d/Shire/herald/spells/lammen";
inherit "/d/Shire/herald/spells/engwagalad";

#include <stdproperties.h>
#include "/d/Shire/herald/herald.h"

public void
create_object()
{
    set_name("crystal");
    add_name("_shire_herald_prayerbook_");
    add_name(({"polished crystal", "crystal", "long polished crystal"}));
    add_adj(({"polished", "long"}));
    set_short("long polished crystal");
    set_long("This is a long piece of crystal. It is polished and smooth, and is a gift from the Valar to you. The crystal has been imbued with faint starlight that surrounds it, seeming to glow before your eyes. Within the crystal are the likeness of fourteen figures. They are lifelike in appearence, full of majesty and beauty. One Vala is crowned and stands beside a Valie. Beneath their feet is some writing.\n");

    add_item(({"valar"}),
        "They are beings who watch over and govern Arda. They are seven male and seven Valier, all clothed in great power and majesty.\n");
    add_item(({"seven male", "seven male valar"}),
        "They are the male Valar who watch over Arda. Their images can be seen in the crystal, clothed in power and great glory.\n");
    add_item(({"valier"}),
        "They are the Seven Queens of the Valar. They are arrayed with power and majesty in their own right. Their likenesses can be seen in the crystal.\n");
    add_item(({"first figure", "manwe"}),
        "This first figure is the mightiest of the Valar and spouse of Varda. He wears a silver crown, bears a scepter made of sapphire, and is arrayed in blue.\n");
    add_item(({"second figure", "varda", "elbereth", "first valier", 
            "first valie", "tintalle", "gilthoniel", "elentary", 
            "lady of the stars", "fanuilos", "snow white", "snow-white"}),
        "This second figure is that of Varda, spouse of Manwe and the mightiest of the Valier. She is arrayed in shining white and also known as Elbereth.\n");
    add_item(({"third figure", "ulmo", "lord of waters", "king of the sea"}),
       "This third figure is of Ulmo and lord of the waters. He is arrayed in mail of emerald and silver.\n");
    add_item(({"fourth figure", "aule", "mahal", "smith", "maker"}),
        "This fourth figure is of Aule, named Mahal by dwarves. He is the master of all crafts and deviser of metals and gemstones.\n");
    add_item(({"fifth figure", "yavanna", "kementari", "queen of the earth"}),
        "This fifth figure is Yavanna, spouse of Aule. Also known as Kemntari, her tall, graceful form is arrayed with a green robe lit with with golden dew.\n");
    add_item(({"sixth figure", "mandos", "namos", "doomsman of the valar"}),
        "This sixth figure is that of Mandos, also known as Namos and spouse of Vaire. He bears a inflexible and dispassionate countenance.\n");
    add_item(({"seventh figure", "nienna"}),
        "This seventh figure is of Nienna. Her tearful appearance of hope, pity, and endurance is inspiring.\n");
    add_item(({"eighth figure", "orome", "araw", "bema", "aldaron", "tauron", "orome the great", "great rider"}),
        "This eigthth figure is of Orome. He is  riding a great steed and is the spouse of Vana. His strong expression is that of a great hunter.\n");
    add_item(({"ninth figure", "vana", "ever-young"}),
         "This ninth figure is of Vana and the spouse of Orome. She is also known as Ever-young for her youthful appearance.\n");
    add_item(({"tenth figure", "nessa"}),
        "This tenth figure is of Nessa, spouse of Tulkas. Her lithe and swift figure marks her as a dancer.\n");
    add_item(({"eleventh figure", "tulkas"}),
        "This eleventh figure is that of Tulkas, spouse of Nessa and the strongest of the Valar. He has golden hair and beard, and a ruddy complexion.\n");
    add_item(({"twelfth figure", "irmo", "lorien"}),
        "This twelfth figure is that of Lorien. He is fair looking and the spouse of Este.\n");
    add_item(({"thirteenth figure", "este"}),
         "This thirteenth figure is Este, spouse of Irmo. Her gentle demeanor is a welcome relief to many. She is clothed in grey.\n");
    add_item(({"fourteenth figure", "vaire"}),
        "This fourteen figure is that of Vaire, spouse of Mandos. She looks wise in things that are to be.\n");
    add_item(({"writing"}),
        "They are words that seem to float beneath the feet of the figures. The flowing, graceful words may be read.\n");
    add_item(({""}),
        "\n");
    add_item("sign", "Maybe you should read it.\n");
    add_cmd_item(({"words", "writing"}), "read", "@@read_words@@");
                        
         
   

    add_spell("mel", "praise Lorien", create_mel_spell, 
      spell_target_caster_environment);
    add_spell("ramar", "summon a messenger", create_ramar_spell,
      spell_target_caster_environment);
    add_spell("palandir", "sense other Heralds", create_palandir_spell,
      spell_target_caster_environment);
    add_spell("khil", "divine one's alignment", create_khil_spell,
      spell_target_one_other_present_living);
    add_spell("haetir", "view someone from afar", create_haetir_spell,
      spell_target_one_distant_known_living, 1);
    add_spell("silme", "produce an aura of light", create_silme_spell, 
      spell_target_herald_robe);
    add_spell("vanahwesta", "decrease anger", create_vanahwesta_spell,
      spell_target_caster_environment, 1);
    add_spell("ondo", "robe of stone", create_ondo_spell,
      spell_target_herald_robe);
    add_spell("lissinen", "tend someones wounds", create_lissinen_spell,
      spell_target_one_present_living, 1);
    add_spell("engwagalad", "cure someone from poisoning",
      create_engwagalad_spell, spell_target_one_present_living, 1);
    add_spell("lammen", "speak with the voice of Manwe", create_lammen_spell,
      spell_target_caster);

    add_prop(OBJ_I_WEIGHT,   1200);           /* 1.2 kg        */
    add_prop(OBJ_I_VOLUME,    500);           /* Empty volume. */
    add_prop(OBJ_M_NO_SELL,     1);
    add_prop(OBJ_M_NO_STEAL,    1);
    add_prop(OBJ_I_NO_DROP,     1);
    add_prop(OBJ_M_NO_GIVE,     1);
    remove_prop(OBJ_I_VALUE);
}


string read_words()
{
    return"This crystal describes the ingredients necessary for each of\n" +
        "your spells.\n\n"+
        "> The prayer vanahwesta, to Orome, requires a brown mushroom.\n" +
        "> The lissinen prayer, to Lorien, requires a huckleberry.\n" +
        "> The prayer for engwagalad, to Este, needs athelas to be " +
            "effective.\n" +
        "  Adding pawnrose will boost the prayer's effectiveness.\n"+
        "> The haetir prayer is granted through Manwe with a parsley leaf.\n"+
        "> The ondo spell of Aule needs a rock for success.\n"+
        "> The prayers mel, silme, ramar, palandir, lammen and khil do not\n"+
        "  require ingredients.\n\n";
}

void
enter_env(object env, object from)
{
    ::enter_env(env, from);
    if (IS_MEMBER(env) || env->query_wiz_level())
	add_spell_object(env);
}

void
leave_env(object env, object to)
{
    ::leave_env(env, to);
    remove_spell_object(env);
}

public int
query_recover()
{
    return 0;
}
