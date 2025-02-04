#pragma once

#include <cstdint>
#include <memory>
#include <string>
#include <array>

// We need the DBGameAssets and CoDAssetType classes
#include "DBGameAssets.h"
#include "CoDAssetType.h"

// Handles reading from Black Ops 2
class GameBlackOps2
{
public:
    // -- Game functions

    // Loads offsets for Black Ops 2
    static bool LoadOffsets();
    // Loads assets for Black Ops 2
    static bool LoadAssets();

    // TODO: Read functions for xanim, xmodel, xfx (Make generic types to translate to)

    // Reads an XAnim from Black Ops 2
    static std::unique_ptr<XAnim_t> ReadXAnim(const CoDAnim_t* Animation);
    // Reads a XModel from Black Ops 2
    static std::unique_ptr<XModel_t> ReadXModel(const CoDModel_t* Model);

    // Reads an XImageDDS from a image reference from Black Ops 2
    static std::unique_ptr<XImageDDS> LoadXImage(const XImage_t& Image);

    // Reads a string via it's string index for Black Ops 2
    static std::string LoadStringEntry(uint64_t Index);

    // Reads a XMap from Black Ops 2
    static std::unique_ptr<XMap_t> ReadXMap(const CoDMap_t* Map);

    static std::vector<BO2MapSurface> ReadMapSufaces(uint64_t address, uint32_t count);

private:
    // -- Game offsets databases

    // A list of offsets for Black Ops 2 single player
    static std::array<DBGameInfo, 1> SinglePlayerOffsets;
    // A list of offsets for Black Ops 2 multi player
    static std::array<DBGameInfo, 1> MultiPlayerOffsets;
    // A list of offsets for Black Ops 2 zombie mode
    static std::array<DBGameInfo, 1> ZombieModeOffsets;

    // -- Game utilities

    // Reads an XMaterial from it's logical offset in memory
    static const XMaterial_t ReadXMaterial(uint64_t MaterialPointer);
};