#include "/d/Krynn/common/defs.h"
#include "../local.h"

#include <ss_types.h>
#include <wa_types.h>
#include <language.h>
#include <macros.h>

inherit M_FILE

int react_grope_new(object who, string adverb);
int react_hug_new(object who, string adverb);
string what_me();

create_krynn_monster()
{
    set_name("willa");
    set_adj("dimpled");
    set_adj("pretty");
    add_name(({"girl", "woman", "female", "waitress", "servant"}));
    set_race_name("human");
    set_gender(1);
    set_long("This sweet young girl looks like she is eager to help. " +
	     "Treat her nicely and she will bring you the best of what the "+
	     "kitchen has to offer.\nShe is wearing her hair in a long "+
	     "braid.\n");
    set_stats(({50, 75, 50, 60, 50, 40}));
    set_gender(1);
    set_alignment(200);
    
    set_all_hitloc_unarmed(40);
    set_all_attack_unarmed(40, 40);
    
    set_skill(SS_DEFENCE, 40);
    set_skill(SS_WEP_CLUB, 40);
    set_skill(SS_AWARENESS, 20);
    set_skill(SS_UNARM_COMBAT, 40);

    add_prop(NPC_I_NO_LOOKS,1);
    
    set_act_time(5);
    add_act(({"say If you have questions about what is on the menu, just " +
		"ask me.", "emote smooths her apron."}));
    add_act(({"say Doesn't the food smell wonderful?", 
		"emote inhales deeply."}));
    add_act(({"say How can I help you?", 
		"emote smiles shyly."}));
    add_act("squeeze all");
    add_act("bounce happily");
    add_act("emote hums softly to herself."); 
    add_act("emote wipes a table with a rag.");
    add_act("emote tucks a loose strand of hair behind her ear.");
    
    add_ask(({"roast", "capon", "roast capon", "roasted capon"}),
	    "say It is delicious! One serving consists of one-half of "+
	    "a male chicken oven-roasted until the skin is golden-brown, "+
	    "and accompanied with aspic.", 1);
    add_ask("pasta", 
	    "say We serve the pasta in two sizes, large and small", 1);
    add_ask(({"plate", "large pasta", "large plate of pasta"}),
	    "say The large plate of pasta has a yummy tomato sauce poured " +
	    "on top. It smells heavenly, and tastes just as good!", 1);
    add_ask(({"dish", "small dish", "small pasta", "small dish of pasta"}),
	    "say One small dish of pasta consists of thin noodles that have "+
	    "been lightly buttered and salted.", 1);
    add_ask(({"stew", "vegetable stew", "vegetable", "crock", 
		"crock of vegetable stew", "crock of stew"}),
	    "say It is delicious and very filling! The crock is filled with "+
	    "a thick stew made with legumes, potatoes, carrots, celery, " +
	    "onions, and seasoned with herbs. There is even a little cheese " +
	    "grated on top!", 1);
    add_ask(({"bread", "loaf", "loaf of bread", "loaf of whole grain bread"}),
	    "say The loaves of whole grain bread are kneaded by the head " +
	    "cook of the Knights' Spur herself. Made of a tasty combination "+
	    "of whole wheat and rye flours and just the right amount of "+
	    "cornmeal, this bread is light and airy, with a hint of " +
	    "molasses flavour. Caraway seeds are sprinkled on top.",1);
    add_ask("aspic", "say It is a garnish made from gelatin, sherry " +
	    "and the capon stock.", 1);
    add_ask(({"wedge", "wedge of cheese", "brie"}),
	    "say My favorite cheese! It is a wedge of soft, ripened cheese. "+
	    "It has a pungent flavour, a creamy texture, and an edible "+
	    "chalky crust.", 1);
    add_ask(({"ball", "ball of cheese", "cheese ball", "gouda"}),
	    "say Some people are partial to this flattened ball of yellow-orange "+
	    "cheese. It is hard and ripened, with a mild flavour.", 1);   
    add_ask(({"slice", "slice of cheese", "cheese slice", "jarles"}),
	    "say That is a thick slice of pale yellow cheese. It is "+
	    "firm and ripe, with large holes in its interior.", 1);       
    add_ask(({"cube", "cube of cheese", "gjetoest"}), 
	    "say That is a small cube of golden-brown cheese. It is a type "+
	    "of whey cheese, firm and unripened, with a sweet taste.", 1);
    add_ask(({"compote", "berry compote", "berry"}),
	    "say If you like fresh berries you'll love this! It is a small dish " +
	    "of raspberries, strawberries, and blueberries, garnished with " +
	    "a bit of orange peel. Over them has been poured a small " +
	    "portion of thick, sweetened cream.", 1); 
    add_ask(({"fruit", "dried fruit", "package"}), 
	    "say It is a mixture of dried fruits: apples, bananas, apricots, "+
	    "plums, and orange peel, as well as some nuts", 1);
    add_ask(({"cake" }), "say It love it. So chocolaty. Yum.", 1);
    add_ask(({"pudding"}), 
	    "say It is made from medium-grain rice boiled in a mixture of "+
	    "cream, milk, sugar, vanilla, and cinnamon. It smells "+
	    "delicious and should be easy on the stomach.", 1);
    add_ask(({"water"}),
            "say You can get water from Cook in the kitchen. "+
            "Just go north and ask her for water.", 1);
    add_ask(({"wood", "log", "oven", "ovens"}),
            "say I'm too busy serving patrons to run errands for "+
            "Cook. I wish she'd bother someone else about getting "+
            "wood.", 1);

    add_emote_hook("grope", 2.0, react_grope_new);
    add_emote_hook("fondle", 2.0, react_grope_new);
    add_emote_hook("caress", 2.0, react_grope_new);
    add_emote_hook("kiss", 2.0, react_grope_new);
    add_emote_hook("hug", 2.0, react_hug_new); 
    add_emote_hook("squeeze", 2.0, react_hug_new); 
              
    seteuid(getuid(TO));
    if (IS_CLONE)
        set_alarm(0.0, 0.0,"dress_me");
}

void
add_introduced(string name)
{
    command("introduce myself to " + name);
    command("say What can I do for you?");
}

string
what_me()
{
    command("think what she was asked");
    command("say I don't know anything about that.");
    command("blush unhappily");
    return "";
} 


int
react_grope_new(object who, string adverb)
{
    set_alarm(1.0, 0.0, "return_grope", who->query_real_name());
    return 1;
}

int
react_hug_new(object who, string adverb)
{
    set_alarm(1.0, 0.0, "return_hug", who->query_real_name());
    return 1;
}

return_grope(string who)
{
    object obj;
    
    if (obj = present(who, environment()))
      {
	  command("blush angrily");
	  command("slap " + who);
	  command("shout I'm no tavern wench! Unhand me you beast!");
	  return "";
      }
}

return_hug(string who)
{
    object obj;
    
    if (obj = present(who, environment()))
      {
	  command("smile sweetly");
	  command("hug " + who);
	  return "";
      }
}


void
dress_me()
{
   object tray, dress;

   seteuid(geteuid(TO));

   tray = clone_object(SOBJ + "tray");
   tray->move(TO, 1);
   dress = clone_object(SOBJ + "dress");
   dress->move(TO, 1);
   command("wear all");
   command("wield all");
}

EMOTE_HOOK
