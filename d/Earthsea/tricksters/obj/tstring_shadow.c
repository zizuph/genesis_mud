inherit "/std/shadow";

#define SW shadow_who

void pull_back(object who)
{
 object my_owner;
 string item_desc;

 my_owner=SW->query_prop_setting("_trick_i_item_owner");
 if(my_owner!=who)
  {
   item_desc=my_owner->query_prop_setting("_trick_i_tstring_item_desc");

   my_owner->catch_msg("Just as "+who->query_the_name(my_owner)+
     " picks up "+item_desc+" you pull on your string "+"and "+item_desc+
     " lands in your hands.\n");
   who->catch_msg("As you pick up "+item_desc+" it is suddenly yanked "+
     "away from you and lands in the hands of "+
     my_owner->query_the_name(who)+".\n");
   SW->move(my_owner);
  }
 SW->remove_prop("_trick_i_item_owner");
 my_owner->remove_prop("_trick_i_tstring_item_desc");
 my_owner->remove_prop("_trick_i_uses_string");
 remove_shadow();
}

void enter_env(object inv, object from)
{
 set_alarm(0.5,0.0,&pull_back(inv));
}

