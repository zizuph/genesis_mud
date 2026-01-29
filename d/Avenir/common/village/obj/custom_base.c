// -*-C++-*-
// file name: 	  /d/Avenir/common/village/obj/custom_base.c
// creator(s):	  Lilith Jan 2004
// last update:	  
// 		Lucius Oct 2008: Massive cleanup / rewrite.
//
// purpose:         Keeps the mappings and arrays separate,
//                  makes them usable by multiple items.
// note:      
// bug(s):
// to-do:
#pragma strict_types

#include "custom.h"
#include "/d/Avenir/include/macros.h"

inherit "/std/object";
inherit "/lib/commands";
inherit "/lib/wearable_item";

public static string desc, style, colour, fabric;

public static mapping fabric_type = ([       
#include "std_fabrics.h"
]);  

public static string *colours = ({
#include "std_colours.h"
});

public static string *descs = ({
#include "std_descs.h"
"none"
});

public static string *fabrics = m_indices(fabric_type);

static string
mystr(string str)
{
    if (!strlen(str))
	return "";

    return (str == "none" ? "" : str);
}

public void set_desc(string str)       { desc = mystr(str);   }
public void set_style(string str)      { style = mystr(str);  }
public void set_colour(string str)     { colour = mystr(str); }
public void set_fabric(string str)     { fabric = mystr(str); }

public string query_desc(void)         { return desc;    }
public string query_style(void)        { return style;   }
public string query_colour(void)       { return colour;  }
public string query_fabric(void)       { return fabric;  }

public mapping query_fabric_map(void)  { return fabric_type; }


static string
long_desc(void)	{ }

static string
short_desc(void)
{
    if (!strlen(desc))
	return colour +" "+ fabric +" "+ style;
    else
	return desc +" "+ colour +" "+ fabric +" "+ style;
}

public void
create_tailored(void)
{
    set_pname(style);
    set_short(short_desc);
    set_long(long_desc);

    add_item(({"stitching", "stitches"}),
        "They are good, regular stitches.\n");
    
    /* Furs doen't have a 'fabric' type. */
    if (strlen(fabric) && sizeof(fabric_type[fabric]))
    {
	add_item(fabric, fabric_type[fabric][2] +"\n");
	add_prop(OBJ_I_VALUE,
	    (fabric_type[fabric][0] * 10) + 200 + random(100));
    }
    else
    {
	add_prop(OBJ_I_VALUE, 250 + random(150));
    }
}
  
public void
create_object(void)
{
    set_name("garment");
    add_pname(({"clothes", "clothing"}));
    add_adj(({"custom", "sybarun", "sybarite"}));

    add_prop(OBJ_I_WEIGHT, 200 + random(200));
    add_prop(OBJ_I_VOLUME, 400 + random(100));
    add_prop(OBJ_M_NO_SELL, "It is of purely sentimental value.\n");

    if (IS_CLONE)
      set_item_expiration();  	

    set_looseness(20);
    set_layers(2);
}

public void
appraise_object(int num)
{
    ::appraise_object(num);
    appraise_wearable_item();
}

public void
leave_env(object dest, object old)
{
    ::leave_env(dest, old);
    wearable_item_leave_env(dest, old);    
}

static void
custom_recover(string arg)	{ }

public void
init_recover(string arg)
{
    string left;

#if 0
    seteuid(getuid());
    SCROLLING_LOG("/d/Avenir/log/garment",
	TP->query_name() +": "+ arg);
#endif

    init_item_expiration_recover(arg);

    sscanf(arg, "%s#D#%s#S#%s#F#%s#C#%s#N#%s",
	arg, desc, style, fabric, colour, left);

    if (!strlen(style))
    {
	/* This should not happen... */
	remove_object();
	return;
    }

    custom_recover(left);
    create_tailored();
}

static string
query_custom_recover(void)	{ return ""; }

public string
query_recover(void)
{
    return MASTER + ":#D#" + desc +
                     "#S#" + style +
		     "#F#" + fabric +
		     "#C#" + colour +
		     "#N#" + query_custom_recover() 
                   + query_item_expiration_recover();  
}

