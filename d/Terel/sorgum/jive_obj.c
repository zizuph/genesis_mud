inherit "/std/object";
#include <stdproperties.h>

create_object()
{
        set_name("_jive");
        set_long("Jive talker.\n");
 
        add_prop(OBJ_I_INVIS,100);
        add_prop(OBJ_M_NO_DROP,1);
}

query_jive_map()
{
    return ([
    "send":"t'row",
    "takes":"snatch'd",
    "take":"snatch",
    "don't":"duzn't",
    "jive":"JIBE",
    "fool":"honkyfool",
    "man":"dude",
    "woman":"mama",
    "girl":"goat",
    "something":"sump'n",
    "lie":"honky jibe",
    "Sure":"Sho' nuff",
    "sure":"sho' nuff",
    "will":"gots'ta",
    "haven't":"aint",
    "have":"gots'",
    "has":" gots'ta",
    "computer":"clunker",
    "or":"o'",
    "killed":"wasted",
    "injured":"hosed",
    "knew":"knowed",
    "because":"a'cuz",
    "Because":"A'cuz",
    "your":"yo'",
    "Your":"Yo'",
    "four":"foe",
    "got":"gots",
    "aren't":"ain't",
    "young":"yung",
    "you":"ya'",
    "You":"You's",
    "first":"fust",
    "write":"scribble",
    "from":" fum",
    "you're":"youse",
    "You're":"Youse",
    "alright":"coo'",
    "okay":"coo'",
    "known":"knode",
    "want":"wants'",
    "beat":"whup'",
    "like":"likes",
    "did":"dun did",
    "women":"honky chicks",
    "men":"dudes ",
    "mens":"dudes ",
    "man":"dude ",
    "woman":"honky chick",
    "dead":"wasted",
    "good":"baaaad",
    "open":"jimmey ",
    "opened":"jimmey'd ",
    "very":"real",
    "can":"kin",
    "just":"plum ",
    "believe":"recon'",
    "broken":"bugger'd",
    "strange":"funky ",
    "dance":"boogy ",
    "house":"crib",
    "ask":"ax'",
    "so":" so's",
    "head":"'haid",
    "boss":"main man",
    "wife":"mama",
    "people":"sucka's",
    "money":"bre'd",
    "hair":"fro",
    "talk":"rap",
    "music":"beat",
    "basket":"hoop",
    "friend":"homey",
    "school":"farm",
    "boss":"Man",
    "well":"sheeit",
    "Well":"Sheeit",
    "big":"big-ass",
    "bad":"bad-ass",
    "small":"little-ass",
    "is":"be",
    "water":"booze",
    "book":"scribblin'",
    "up":"down",
    "down":"waaay down",
    "break":"boogie",
    "Hi":"'Sup: dude"]);
}
    
    
init()
{
        ::init();
        add_action("say","say");
}

say(string s)
{
    string *str,ss;
    mapping mapp;
    int i,a,b;
 
    if(!s)
        return 0;
 
    mapp = query_jive_map();
 
    str = explode(s," ");
 
    for (i = 0; i < sizeof(str); i++) {
	ss = mapp[str[i]];
	if(ss)
	    str[i] = ss;
    }    
    this_player()->communicate(implode(str," "));
            
    return 1;
}
 
 
