package com.mymyka.npc;

import com.mymyka.player.Player;

public class TradableNPCDecorator extends NPCDecorator implements Tradable {
    public TradableNPCDecorator(NPC npc) {
        super(npc);
    }

    @Override
    public void sayHello(Player player) {
        super.sayHello(player);
        System.out.println("Do you want trade ?");
        startTradWith(player);
    }

    @Override
    public void startTradWith(Player player) {
        System.out.println("Started trade with: " + player.getName());
    }
}
