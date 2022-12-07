package com.mymyka.npc;

public class TradableNPCDecorator extends NPCDecorator {
    public TradableNPCDecorator(NPC npc) {
        super(npc);
    }

    @Override
    public void spawn() {
        super.spawn();
        System.out.println("Hello ! Do you want to trade ?");
    }
}
