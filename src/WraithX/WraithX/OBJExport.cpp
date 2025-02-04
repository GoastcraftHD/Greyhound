#include "stdafx.h"

// The class we are implementing
#include "OBJExport.h"

// We need the textwriter, hashing, and filesystems classes
#include "TextWriter.h"
#include "Strings.h"
#include "FileSystems.h"

void WavefrontOBJ::ExportOBJ(const WraithModel& Model, const std::string& FileName, bool CombineMtls)
{
    std::string MtlFileName = FileName.substr(0, FileName.size() - 4);
    MtlFileName.erase(0, MtlFileName.find_last_of("\\") + 1);

    // Create a new writer
    auto Writer = TextWriter();
    // Open the model file
    Writer.Create(FileName);
    // Set buffer
    Writer.SetWriteBuffer(0x100000);
    // Write the header
    Writer.WriteLine(
        "# Generated by Wraith - Game extraction tools\n"
        "# Please credit DTZxPorter for using it!\n"
        );
    // Iterate over the submesh (Positions)
    for (auto& Submesh : Model.Submeshes)
    {
        // Iterate over faces
        for (auto& Face : Submesh.Faces)
        {
            // Write positions
            Writer.WriteLineFmt(
                "v %f %f %f %f %f %f %f\n"
                "v %f %f %f %f %f %f %f\n"
                "v %f %f %f %f %f %f %f",
                Submesh.Verticies[Face.Index1].Position.X, Submesh.Verticies[Face.Index1].Position.Y, Submesh.Verticies[Face.Index1].Position.Z, (float)Submesh.Verticies[Face.Index1].Color[0] / 255, (float)Submesh.Verticies[Face.Index1].Color[1] / 255, (float)Submesh.Verticies[Face.Index1].Color[2] / 255, (float)Submesh.Verticies[Face.Index1].Color[3] / 255,
                Submesh.Verticies[Face.Index2].Position.X, Submesh.Verticies[Face.Index2].Position.Y, Submesh.Verticies[Face.Index2].Position.Z, (float)Submesh.Verticies[Face.Index2].Color[0] / 255, (float)Submesh.Verticies[Face.Index2].Color[1] / 255, (float)Submesh.Verticies[Face.Index2].Color[2] / 255, (float)Submesh.Verticies[Face.Index2].Color[3] / 255,
                Submesh.Verticies[Face.Index3].Position.X, Submesh.Verticies[Face.Index3].Position.Y, Submesh.Verticies[Face.Index3].Position.Z, (float)Submesh.Verticies[Face.Index3].Color[0] / 255, (float)Submesh.Verticies[Face.Index3].Color[1] / 255, (float)Submesh.Verticies[Face.Index3].Color[2] / 255, (float)Submesh.Verticies[Face.Index3].Color[3] / 255
                );
        }
    }
    // Iterate over the submesh (UVs)
    for (auto& Submesh : Model.Submeshes)
    {
        // Iterate over faces
        for (auto& Face : Submesh.Faces)
        {
            // Write uvs
            Writer.WriteLineFmt(
                "vt %f %f\n"
                "vt %f %f\n"
                "vt %f %f",
                Submesh.Verticies[Face.Index1].UVLayers[0].U, (1 - Submesh.Verticies[Face.Index1].UVLayers[0].V),
                Submesh.Verticies[Face.Index2].UVLayers[0].U, (1 - Submesh.Verticies[Face.Index2].UVLayers[0].V),
                Submesh.Verticies[Face.Index3].UVLayers[0].U, (1 - Submesh.Verticies[Face.Index3].UVLayers[0].V)
                );
        }
    }
    // Iterate over the submesh (Normals)
    for (auto& Submesh : Model.Submeshes)
    {
        // Iterate over faces
        for (auto& Face : Submesh.Faces)
        {
            // Write normals
            Writer.WriteLineFmt(
                "vn %f %f %f\n"
                "vn %f %f %f\n"
                "vn %f %f %f",
                Submesh.Verticies[Face.Index1].Normal.X, Submesh.Verticies[Face.Index1].Normal.Y, Submesh.Verticies[Face.Index1].Normal.Z,
                Submesh.Verticies[Face.Index2].Normal.X, Submesh.Verticies[Face.Index2].Normal.Y, Submesh.Verticies[Face.Index2].Normal.Z,
                Submesh.Verticies[Face.Index3].Normal.X, Submesh.Verticies[Face.Index3].Normal.Y, Submesh.Verticies[Face.Index3].Normal.Z
                );
        }
    }

    // A list of unique materials
    std::unordered_set<int32_t> UniqueMaterials;
    // The offset buffer
    uint32_t VertexIndex = 1;
    // Iterate over the submesh (Faces)
    for (auto& Submesh : Model.Submeshes)
    {
        // Grab a reference to material
        const WraithMaterial& Material = (Submesh.MaterialIndicies[0] > -1) ? Model.Materials[Submesh.MaterialIndicies[0]] : WraithMaterial::DefaultMaterial;
        // Output the material info
        Writer.WriteLineFmt(
            "mtllib %s.mtl\n"
            "g %s\n"
            "usemtl %s",
            CombineMtls ? MtlFileName.c_str() : Material.MaterialName.c_str(),
            Material.MaterialName.c_str(),
            Material.MaterialName.c_str()
            );// Add
            UniqueMaterials.insert(Submesh.MaterialIndicies[0]);
        // Iterate over faces
        for (auto& Face : Submesh.Faces)
        {
            // Write faces
            Writer.WriteLineFmt(
                // The format chunks, 3 pairs of 3
                "f %d/%d/%d %d/%d/%d %d/%d/%d",
                (VertexIndex + 2), (VertexIndex + 2), (VertexIndex + 2),
                (VertexIndex + 1), (VertexIndex + 1), (VertexIndex + 1),
                VertexIndex, VertexIndex, VertexIndex
                );
            // Advance
            VertexIndex += 3;
        }
    }
    // Prepare to make materials if need be
    auto MaterialPath = FileSystems::GetDirectoryName(FileName);

    // Make a new writer
    TextWriter MatWriter;

    if (CombineMtls)
    {
        MatWriter = TextWriter();
        // Make the material
        MatWriter.Create(FileSystems::CombinePath(MaterialPath, MtlFileName + ".mtl"));
    }

    // Iterate over unique group
    for (auto& MaterialIndex : UniqueMaterials)
    {
        // Grab a reference to material
        const WraithMaterial& Material = (MaterialIndex > -1) ? Model.Materials[MaterialIndex] : WraithMaterial::DefaultMaterial;

        if (!CombineMtls)
        {
            // Make a new writer
            MatWriter = TextWriter();
            // Make the material
            MatWriter.Create(FileSystems::CombinePath(MaterialPath, Material.MaterialName + ".mtl"));
        }

        // Write header
        MatWriter.WriteLineFmt("\nnewmtl %s", Material.MaterialName.c_str());
        // Basic info
        MatWriter.WriteLine("illum 4\nKd 0.00 0.00 0.00\nKa 0.00 0.00 0.00\nKs 0.50 0.50 0.50");
        // Output maps
        if (!Strings::IsNullOrWhiteSpace(Material.DiffuseMapName))
        {
            // Output color map
            MatWriter.WriteLineFmt("map_Kd %s", Material.DiffuseMapName.c_str());
        }
        if (!Strings::IsNullOrWhiteSpace(Material.NormalMapName))
        {
            // Output normal map
            MatWriter.WriteLineFmt("map_bump %s", Material.NormalMapName.c_str());
        }
        if (!Strings::IsNullOrWhiteSpace(Material.SpecularMapName))
        {
            // Output specular map
            MatWriter.WriteLineFmt("map_Ks %s", Material.SpecularMapName.c_str());
        }
    }
}