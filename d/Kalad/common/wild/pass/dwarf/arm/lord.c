   set_af(TO);
   add_prop(OBJ_I_IS_MAGIC_ARMOUR,1);
   add_prop(OBJ_S_WIZINFO,"This breastplate is enchanted, making "+
   "the player punishment in less mana, -50.\n");
   add_prop(MAGIC_AM_ID_INFO,({"With your newly gained knowledge "+
      "and be fully consentrated to dare to wear it.\n",30}));
   add_prop(MAGIC_AM_MAGIC, ({ 30, "enchantment" }));
}

mixed
wear(object what)
{
   return 0;
}

mixed
remove(object what)
{
   return 0;
}
