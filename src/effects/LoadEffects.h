/**********************************************************************

  Audacity: A Digital Audio Editor

  LoadEffects.h

  Dominic Mazzoni

**********************************************************************/

#include "audacity/ModuleInterface.h"
#include "audacity/EffectInterface.h"
#include "audacity/PluginInterface.h"

#include "Effect.h"
#include "../MemoryX.h"

///////////////////////////////////////////////////////////////////////////////
//
// BuiltinEffectsModule
//
///////////////////////////////////////////////////////////////////////////////

class BuiltinEffectsModule final : public ModuleInterface
{
public:
   BuiltinEffectsModule(ModuleManagerInterface *moduleManager, const wxString *path);
   virtual ~BuiltinEffectsModule();

   // ComponentInterface implementation

   PluginPath GetPath() override;
   ComponentInterfaceSymbol GetSymbol() override;
   VendorSymbol GetVendor() override;
   wxString GetVersion() override;
   wxString GetDescription() override;

   // ModuleInterface implementation

   bool Initialize() override;
   void Terminate() override;

   wxArrayString GetFileExtensions() override { return {}; }
   wxString InstallPath() override { return {}; }

   bool AutoRegisterPlugins(PluginManagerInterface & pm) override;
   PluginPaths FindPluginPaths(PluginManagerInterface & pm) override;
   unsigned DiscoverPluginsAtPath(
      const PluginPath & path, wxString &errMsg,
      const RegistrationCallback &callback)
         override;

   bool IsPluginValid(const PluginPath & path, bool bFast) override;

   ComponentInterface *CreateInstance(const PluginPath & path) override;
   void DeleteInstance(ComponentInterface *instance) override;

private:
   // BuiltinEffectModule implementation

   std::unique_ptr<Effect> Instantiate(const PluginPath & path);

private:
   ModuleManagerInterface *mModMan;
   PluginPath mPath;

   PluginPaths mNames;
};
