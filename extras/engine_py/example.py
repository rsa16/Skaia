from skaia.components import Transform, Sprite, Input
from skaia.core import Coordinator, System
import skaia
import cppyy.ll

coordinator = Coordinator()

class PlayerMovement(System):
    def __init__(self, c: Coordinator):
        self.coordinator = c
        
        signature = skaia.Signature()
        signature.set(self.coordinator.GetComponentType[Input]())
        self.coordinator.SetSystemSignature[PlayerMovement](signature)

        super().__init__()

    def Initialize(self, data):
        print("Player movement system initialized!")

    def Render(self):
        pass

    def Cleanup(self):
        pass

    def Update(self):
        for entity in self.mEntities:
            entityInput = self.coordinator.GetComponent[Input](entity)
            entityTransform = self.coordinator.GetComponent[Transform](entity)

            if (entityInput.UP_PRESSED):
                entityTransform.y -= 10

            if (entityInput.DOWN_PRESSED):
                entityTransform.y += 10
            
            if (entityInput.RIGHT_PRESSED):
                entityTransform.x += 10

            if (entityInput.LEFT_PRESSED):
                entityTransform.x -= 10

def main():
    print("Creating game application...")
    game = skaia.GameApplication(coordinator, "Test", 500, 600)

    print("Tracking our custom system and turning on our fps counter")
    game.TrackSystem[PlayerMovement]() # give the game our player movement system
    game.SetCounterOn() # turn on fps counter

    print("Fps counter turned on, creating entities")
    player = coordinator.CreateEntity() # skaia.Entity
    coordinator.AddComponent(player, Transform(
        x = (500 / 2) - (100 / 2), # place in horizontal center
        y = (600 / 2) - (100 / 2), # place in vertical center,
        width = 100,
        height = 100
    ))

    coordinator.AddComponent(player, Sprite(
        color = (0, 255, 255)
    ))

    coordinator.AddComponent(player, Input())
    print("Components added, starting game")

    game.Start()

if __name__ == "__main__":
    main()