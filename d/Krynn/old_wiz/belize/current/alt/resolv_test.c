inherit "/std/object";

#include <tasks.h>
#include <ss_types.h>


int diff, ss_spell, ss_lang;

create_object()
{
    set_short("resolve_task tester");
    set_name("tester");
}

void
init()
{
    ::init();
    add_action("test", "test");
    add_action("set", "set");
}

int
set(string str)
{
    string *words;
    
    notify_fail("Set what? Perhaps diff?\n");
    
    if (!strlen(str))
        return 0;
    
    words = explode(str, " ");

    if (sizeof(words) != 2)
        return notify_fail("Bad args.\n");

    switch(words[0])
    {
        case "diff" : diff = atoi(words[1]); break;
        case "w_spell" : ss_spell = atoi(words[1]); break;
        case "w_lang" : ss_lang = atoi(words[1]); break;
        default: return notify_fail("Set diff, w_spell or w_lang?\n");
    }
        
        
    diff = atoi(words[1]);
    
    return 1;
}

int 
test(string num)
{
   int ix, max, min, sum, res, cycles;
   
   cycles = atoi(num);
   
   min = 1000; max = -1000; sum = 0;
   for (ix = 0; ix < cycles; ix++)
   {
        res = this_player()->resolve_task(diff, ({ SKILL_WEIGHT, ss_spell, 
            SS_SPELLCRAFT, SKILL_WEIGHT, ss_lang, SS_LANGUAGE }) );
     write(res + ", ");
          
     if (res < min) min = res;
     if (res > max) max = res;
     sum += res;
    }
    write(".\nDiff: " + diff + "; Cycles: " + cycles + 
        "\nLanguage weight: " + ss_lang + "; Spellcraft weight: " + ss_spell + 
        "\nMin: "+ min + ", Max: " + max + ", Avg: " + (sum/cycles) +
        ", Amplitude: " + (max - min) + ".\n");
    
}
