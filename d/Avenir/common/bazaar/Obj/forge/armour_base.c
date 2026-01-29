// -*-C++-*-
// file name: 	  /d/Avenir/common/bazaar/Obj/forge/armour_base.c
// creator(s):	  Lilith June 1998
// revision(s):	  
// purpose:       
// note:          
// bug(s):
// to-do:

inherit "/std/armour";
inherit "/lib/keep";

int load;
string colour, lining, llong, style, astyle, 
       slong, decor, plating, owner, none;

public void set_lining(string str)     {    lining = str;    }
public void set_line_long(string str)  {    llong = str;     }
public void set_colour(string str)     {    colour = str;    }
public void set_decor(string str)      {    decor = str;     }
public void set_style(string str)      {    style = str;     }
public void set_arm_style(string str)  {    astyle = str;    }
public void set_style_long(string str) {    slong = str;     }
public void set_plating(string str)    {    plating = str;   }
public void set_owner(string str)      {    owner = str;     }
public void set_load(int i)            {    load = i;        }

public string query_colour()           {    return colour;   }
public string query_decor()            {    return decor;     }
public string query_style()            {    return style;    }
public string query_style_long()       {    return slong;    }
public string query_arm_style()        {    return astyle;   }
public string query_plating()          {    return plating;  }
public string query_lining()           {    return lining;   }
public string query_line_long()        {    return llong;    }
public string query_owner()            {    return owner;    }


public void
create_armour()
{
    seteuid(getuid());

    set_name("_Avenir_specialty_armour");
    set_keep(1);

    if (random(2))
	set_may_recover();
}

public void
add_knotwork()
{
    add_item(({"knotwork", "knots"}), "Geometrically symmetrical "+
       "lines that seem to flow into and through each other.\n");
}
