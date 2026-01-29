inherit "/std/object";
#include "/d/Kalad/defs.h"
#include "/d/Kalad/common/noble/arm/ring.h"
#define SUBLOC "wearing_pierced_subloc"

int check_double(string str);
int check_hidden(object ob, object carrier);
int check_hiddens(string st, object carrier);

query_auto_load()
{
   return MASTER;
}

/* by Sarr */

void
create_object()
{
   set_name("pierce2");
   add_name("brilderisreallyaniceguy");
   set_long("right ear pierced.\n");
   set_short("right ear");
   add_prop(OBJ_I_VALUE,144);
   add_prop(OBJ_I_INVIS,100);
   add_prop(KALAD_RING_HOLE,1);
   add_prop(OBJ_M_NO_DROP,1);
   set_no_show();
}

void
enter_env(object to, object from)
{
   if (living(to))
   {
      to->add_subloc(SUBLOC, this_object());
      to->add_prop(KALAD_RING_EAR_RIGHT,1);
   }
   ::enter_inv(to, from);
}

void
leave_env(object from, object to)
{
   if (living(from))
   {
      from->remove_subloc(SUBLOC);
      from->remove_prop(KALAD_RING_EAR_RIGHT);
   }
   ::leave_env(from, to);
}

int
check_double(string str)
{
    if(str == "ears")
        return 1;
    if(str == "nipples")
        return 1;
    if(str == "eyebrows")
        return 1;
    return 0;
}

string
show_subloc(string subloc, object carrier, object for_obj)
{
   int i;
   string str,*holes, non,*holes_me;
   object *ob,*ob2,*obs_me,c;
   holes = ({});
   holes_me = ({});
   c = carrier;
   ob2 = all_inventory(carrier);
   ob = carrier->subinventory(SUBLOC);
   obs_me = carrier->subinventory(SUBLOC);
   if (carrier->query_prop(TEMP_SUBLOC_SHOW_ONLY_THINGS))
      return "";
   if (for_obj == carrier)
      str = "You";
   else
      str = C(HE(carrier));
   if(for_obj == carrier)
       non  = "your";
   else
       non = HIS(carrier); 
   for(i=0;i<sizeof(ob2);i++)
   {
       if( ob2[i]->query_prop(KALAD_RING_HOLE) )
       {
           holes_me += ({ ob2[i]->query_short() });
           holes += ({ ob2[i]->query_short() });
       }
   }
   for(i=0;i<sizeof(ob);i++)
   {
       if(check_hidden(ob[i],c))
           ob -= ({ ob[i] });
   }
   for(i=0;i<sizeof(holes);i++)
   {
       if(check_hiddens(holes[i],c))
           holes -= ({holes[i]});
   }
    if(for_obj == carrier) /* If we're us looking at us..... */
    {
        if(sizeof(obs_me))
        {
            str = str + " are wearing a ";
            for(i=0;i<sizeof(obs_me) - 2;i++)
            {
                str = str + obs_me[i]->short()+ " in "+non+
                " "+obs_me[i]->query_prop(KALAD_RING_LOCATION);
                if(check_hidden(obs_me[i],c))
                    str = str +"(hidden behind armour), ";
                else
                    str = str +", ";
                holes_me -= ({ obs_me[i]->query_prop(KALAD_RING_LOCATION) });
            }
            if(sizeof(obs_me) == 1)
            {
                str = str + obs_me[i]->short()+" in "+non+
                " "+obs_me[i]->query_prop(KALAD_RING_LOCATION);
                if(check_hidden(obs_me[i],c))
                   str = str +"(hidden behind armour)";
                holes_me -= ({ obs_me[i]->query_prop(KALAD_RING_LOCATION) });
            }
            else
            {
                str = str + obs_me[i]->short()+" in "+non+
                " "+obs_me[i]->query_prop(KALAD_RING_LOCATION);
                if(check_hidden(obs_me[i],c))
                    str = str +"(hidden behind armour)";
                str = str +" and a "+ 
                obs_me[i + 1]->short()+" in "+non+" "+
                obs_me[i+1]->query_prop(KALAD_RING_LOCATION);
                if(check_hidden(obs_me[i+1],c))
                    str = str +"(hidden behind armour)";
                holes_me -= ({ obs_me[i]->query_prop(KALAD_RING_LOCATION),
                            obs_me[i+1]->query_prop(KALAD_RING_LOCATION) });
             }
             if(sizeof(holes_me))
             {
                 str = str +" and ";
                 if(check_double(holes_me[0]))
                     str = str + "have pierced ";
                 else
                     str = str + "have a pierced ";
             }
             else
                return str + ".\n";
        }
        if(sizeof(holes_me))
        {
            if(!sizeof(obs_me)) /* Should we add "have pierced" ? only */
                                /* if the player is not wearing anything */ 
                                /* cuz, its taken care of if s/he was    */
            {
                if(check_double(holes_me[0]))
                    str = str + " have pierced ";
                else
                    str = str + " have a pierced ";
            } 
            for(i=0;i<sizeof(holes_me) - 2;i++)
            {
                str = str + holes_me[i];
                if(check_hiddens(holes_me[i],c))
                    str = str +"(hidden by armour), ";
                else
                    str = str + ", ";
            }
            if(sizeof(holes_me) == 1)
            {
                if(check_hiddens(holes_me[i],c))
                    str = str + holes_me[i]+"(hidden by armour)";
                else
                    str = str + holes_me[i];
            }
            else
            {
                if(check_hiddens(holes_me[i],c))
                    str = str + holes_me[i]+"(hidden by armour)";
                else
                    str = str + holes_me[i];
                if(check_hiddens(holes_me[i+1],c))
                    str = str +" and "+holes_me[i+1]+"(hidden by armour)";
                else
                    str = str +" and "+holes_me[i+1];
            }
            if(sizeof(holes_me) == 1)
                if(check_double(holes_me[0]))
                    return str + " with no rings in them.\n";
                else   
                    return str + " with no ring in it.\n";
            else
                return str + " with no rings in them.\n";
        }
   }
   else /* Otherwise, its an on-looker */
   {
       if(sizeof(ob))
       {
           str = str + " is wearing a ";
           for(i=0;i<sizeof(ob) - 2;i++)
           {
               str = str + ob[i]->short()+ " in "+non+
               " "+ob[i]->query_prop(KALAD_RING_LOCATION)+", ";
               holes -= ({ ob[i]->query_prop(KALAD_RING_LOCATION) });
           }
           if(sizeof(ob) == 1)
           {
               str = str + ob[i]->short()+" in "+non+
               " "+ob[i]->query_prop(KALAD_RING_LOCATION);
               holes -= ({ ob[i]->query_prop(KALAD_RING_LOCATION) });
           }
           else
           {
               str = str + ob[i]->short()+" in "+non+
               " "+ob[i]->query_prop(KALAD_RING_LOCATION)+ " and a "+ 
               ob[i + 1]->short()+" in "+non+" "+
               ob[i+1]->query_prop(KALAD_RING_LOCATION);
               holes -= ({ ob[i]->query_prop(KALAD_RING_LOCATION),
                           ob[i+1]->query_prop(KALAD_RING_LOCATION) });
           }
           if(sizeof(holes))
           {
               str = str +" and ";
               if(check_double(holes[0]))
                   str = str + "has pierced ";
               else
                   str = str + "has a pierced ";
           }
           else
               return str + ".\n";
       }
       if(sizeof(holes))
       {
           if(!sizeof(ob))
           {
               if(check_double(holes[0]))
                   str = str + " has pierced ";
               else
                   str = str + " has a pierced ";
           }
           for(i=0;i<sizeof(holes) - 2;i++)
           {
               str = str + holes[i] + ", ";
           }
           if(sizeof(holes) == 1)
               str = str + holes[i];
           else
               str = str + holes[i] + " and " + holes[i + 1];
           if(sizeof(holes) == 1)
               if(check_double(holes[0]))
                   return str + " with no rings in them.\n";
               else   
                   return str + " with no ring in it.\n";
           else
               return str + " with no rings in them.\n";
       }
      return "";
   }
}

int
check_hidden(object what, object carrier)
{
    string loc;
    loc = what->query_prop(KALAD_RING_LOCATION);
    switch(loc)
    {
        case "left ear":
        case "right ear":
        case "ears":
            if(carrier->query_armour(TS_HEAD))
                return 1;
            else
                return 0;        
            break;
        case "left nipple":
        case "right nipple":
        case "nipples":
        case "navel":
            if(carrier->query_armour(TS_TORSO))
                return 1;
            else
                return 0;
            break;
        default:
            return 0;
            break;
    }
}

int
check_hiddens(string where, object carrier)
{
    switch(where)
    {
        case "left ear":
        case "right ear":
        case "ears":
            if(carrier->query_armour(TS_HEAD))
                return 1;
            else
                return 0;        
            break;
        case "left nipple":
        case "right nipple":
        case "nipples":
        case "navel":
            if(carrier->query_armour(TS_TORSO))
                return 1;
            else
                return 0;
            break;
        default:
            return 0;
            break;
    }
}
