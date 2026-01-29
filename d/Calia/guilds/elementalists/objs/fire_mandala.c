/*
 * Mandala for the Elemental Fire Clerics
 *
 * Created by Jaacar, July 2016
 */


#pragma save_binary
#pragma strict_types

#include <stdproperties.h>
#include <cmdparse.h>
#include <macros.h>
#include <tasks.h>
#include <ss_types.h>
#include <wa_types.h>
#include "defs.h"

inherit ELEMENTALIST_OBJS + "power_tool_base";

// Defines

// Global Variables
string color1 = "red";
string color2 = "copper";

/*
 * Function:    create_power_tool
 * Description: Override this to customize the power tool
 */
public void
create_power_tool()
{
    set_name("mandala");
    add_name("symbol");
    add_adj(({"sacred",color1,color2}));
    add_name("_elemental_guild_mandala");
    set_short("@@mandala_short@@");
    set_element_flag(FIRE_FLAG);
}

/*
 * Function: mandala_short
 * Description: Show the short description of the mandala
 */
public string
mandala_short()
{
    if (TP->test_bit("Calia", EC_GURU_GROUP, EC_GURU_BIT))
	{
		color1 = "yellow";
		color2 = "crystalline";
	}
	
	return "sacred "+color1+" and "+color2+" mandala";
}

/*
 * Function:    hook_destroy_message
 * Description: Override this hook to show your custom message for the
 *              destruction of the power tool.
 */
public string
hook_destroy_message(object env)
{
    return "The " + short() + " shatters into thousands of tiny pieces.\n";
}

/*
 * Function:    hook_describe_long
 * Description: Override this for the main part of the description for
 *              the power tool. The rune information will be added at
 *              the end.
 */
public string
hook_describe_long()
{
	if (TP->test_bit("Calia", EC_GURU_GROUP, EC_GURU_BIT))
	{
		color1 = "yellow";
		color2 = "crystalline";
	}
	
    return "This " + short() + " is the holy symbol of Pyros. "+
        "It is a small round "+color1+" symbol with a pattern of "+
        color2+" lines in the middle. The <pattern> consists of a circle "+
        "with a square inside of it. Inside of the square are three "+
        "wiggly lines running from bottom to top.\n";
}

/*
 * Function:    hook_describe_power_word
 * Description: Returns the power word that should be carved into
 *              the power tool.
 */
public string
hook_describe_power_word()
{
    return "Fotia";
}

/*
 * Function:    hook_describe_deity_name
 * Description: Returns the name of the Deity, which is shown on
 *              the runes on the power tool.
 */
public string
hook_describe_deity_name()
{
    return "Pyros";
}

/*
 * Function:    query_color1
 * Description: Returns the first color of the mandala.
 */
public string
query_color1()
{
    return color1;
}

/*
 * Function:    query_color2
 * Description: Returns the second color of the mandala.
 */
public string
query_color2()
{
    return color2;
}

int
do_clasp(string str)
{
    if (!str)
        return 0;

    if (str != "symbol" && str != "mandala" &&
        str != "sacred mandala")
    {
        NF("Clasp what? Your sacred mandala?\n");
        return 0;
    }

    write("You clasp your sacred mandala and hold it close to your chest.\n");
    say(QCTNAME(TP)+" clasps "+HIS+" sacred "+color1+" and "+color2+
        " mandala and holds it close to "+HIS+" chest.\n");
    return 1;
}

int
do_pattern()
{
	string symbol;

	symbol = "                                                   \n"+                                                   
			"                            ...                    \n"+
			"                           .,,,,.                  \n"+
			"                           .,,,,,.                 \n"+
			"                            .,,,,,.                \n"+
			"                             .:,:,:.               \n"+
			"                              .::::,               \n"+
			"                              .,::::.              \n"+
			"                               .::::,              \n"+
			"                               .::::;.             \n"+
			"                               .:;:;:.             \n"+
			"                               .:;:;:.             \n"+
			"                               .;;;;;.             \n"+
			"                               .;;;;:        .     \n"+
			"                              .:;;;i,       ..     \n"+
			"                              .iiii;.     .;;i;,   \n"+
			"                             .;iiii,     .:i;ii,   \n"+
			"                            .:iiii;      .iiiii.   \n"+
			"            .:;;:.         .,iiiii.     .:iiii:.   \n"+
			"           .:1i1i,        .,1iiii,     .,iiiii.    \n"+
			"            ,i1ii,       .:i1i1i.     .,ii1ii,     \n"+
			"           .;11i1,.     .;1ii1i.     .:i11i1,      \n"+
			"           ,1111i.    .,11i11i...   .i1111i..      \n"+
			"         .,11111.     ,1i111:..   .,ti11ii..       \n"+
			"         ;11111,    .:11111,.     i11111,.         \n"+
			"       .11111i,.   .,t1t11,     ,11111i,.  .       \n"+
			"     .,t111t;.    ..1ttt1,     .i1ttt;.            \n"+
			"     .tt1tt:    . .1tttt,.    .1tttt;.             \n"+
			"    .itttt;.      :1ttt;     .:tttti.              \n"+
			"    :tttt1.      .1tttt,     .ttttt,.              \n"+
			"   .1tttt,.      .fttt1.     ,tttt1.               \n"+
			"   .ttftt.      .,ttft;.     ,ftfti.               \n"+
			"   .tffft.       ,fffti.     .fffft.               \n"+
			"   .iffff:. .    .fffft.     .1fftf:.              \n"+
			"   .,ffftt.      .1ffff:.    .,fffff,.             \n"+
			"    .iffff1.      :fffft.     .;ffffL:.            \n"+
			"     .1LLfLf...   .;fLfft.  .  .:ffLLft..   .      \n"+
			"      .iLffLf1.    .1ffLfL,. .  ..ffLfLft:..       \n"+
			"        ,CfLCfL,   ..;LLfLL..  .  .,fLLCfLL..      \n"+
			"         .;fLLt...  . .tLf:..   .  ..:tfLLL.       \n"+
			"            ..                        ......       \n"+                                                
			 "                                                   \n";

	write("You examine the pattern on your mandala closely:\n"+
	    symbol+"\n");
	return 1;
}

public int
do_touch(string str)
{
    object target = PARSE_COMMAND_ONE(str, 0, "%i");
    if (!target)
    {
        notify_fail("Touch whom with your sacred mandala?\n");
        return 0;
    }
    
    this_player()->catch_msg("You touch your sacred mandala onto "+
        "the forehead of "+(target->query_The_name(this_player())) + 
        " briefly.\n");
    target->catch_msg((TP->query_The_name(target))+" touches "+
        TP->query_possessive()+" sacred mandala onto your forehead briefly. "+
        "Your very soul feels uplifted, almost as if your very essence was "+
        "electrified.\n");
    tell_room(TO,QCTNAME(TP) + " touches "+TP->query_possessive()+
        " sacred mandala onto the forehead of "+QTNAME(target)+" briefly.\n",
        ({target,TP}));
    return 1;
}

void
init()
{
    ::init();
    add_action(do_clasp,"clasp");
    add_action(do_pattern,"pattern");
    add_action(do_touch, "ftouch");
}
