# Foliage Shadow Imposters
A UE5 plugin to add Foliage Shadow Imposters to Nanite Foliage for increased performance when using World Position Offset (WPO) and Virtual Shadow Maps.  We gain performance by disabling the expensive WPO shadow on the Nanite Foliage and replacing it with a cheap non-WPO shadow casting Foliage Shadow Imposter.  The compromise here is that the foliage will animate in the wind, but the shadows cast on the ground will not change.  This comporomise leads to **massive** performance gains.

This plugin searches all InstancedFoliageActors for an OriginalFoliageMesh and adds a FoliageShadowImposterMesh with the same location, rotation, and scale.  The OriginalFoliageMesh should have Nanite Foliage turned on and be set to not cast a shadow in the FoliageType in the Foliage editor.  The OriginalFoliageMesh should have World Position Offset enabled.  The FoliageShadowImposterMesh should be a low poly LOD for the purpose of casting a cheaper shadow.  **The FoliageShadowImposterMesh must have FoliageShadowImposterMesh disabled.**  The plugin will automatically enable the shadow for FoliageShadowImposterMesh, set HiddenInGame, and set cast shadow when hidden.

*This plugin requires Unreal Engine 5.1 or higher.*

Installation Instructions

1. Copy the /src/Plugins/FoliageImposters folder to the /Plugins folder in your UE5 project.
2. Recompile your project in Visual Studio to compile the plugin source code.  It isn't precompiled.
3. Open the UE5 editor and enable the FoliageShadowImposters plugin if it isn't already enabled.
4. Create a DataTable with row type FoliageShadowImposterReplacementRow.
5. Add at least one row to the DataTable.  Specify an OriginalFoliageMesh to search for in the world.  Then pick a FoliageShadowImposterMesh to add to it.  Finally, check the ShouldReplace checkbox.
6. Right click on the new DataTable and click on Copy Reference.
7. Close the editor.
8. Open your DefaultGame.ini file and find the [/Script/EngineSettings.GeneralProjectSettings] section.
9. Add a new line under this section like this.  Paste your refernce inside the double quotes.
```PathToFoliageShadowImposterReplacementDataTable=""```
10. Reopen the editor.
11. Use the Foliage Editor to place the foliage in the world that you specified as OriginalFoliageMesh in step 5.
12. Click on the two trees icon in the toolbar at the top-center of the editor window.  This will add FoliageShadowImposterMesh for each OriginalFoliageMesh it finds.  It will match the location, rotation, and scale of the original.  Each time you run the plugin it will remove all of the FoliageShadowImposterMesh's before it adds them again.  The plugin will only process rows in the DataTable where the ShouldReplace checkbox is checked.
