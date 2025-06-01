#include <windows.h>
#include <wrl.h>
#include <wrl/wrappers/corewrappers.h>
#include <windows.data.xml.dom.h>
#include <windows.ui.notifications.h>

using namespace Microsoft::WRL;
using namespace Microsoft::WRL::Wrappers;
using namespace ABI::Windows::Data::Xml::Dom;
using namespace ABI::Windows::UI::Notifications;

#pragma comment(lib, "windowsapp")
#pragma comment(lib, "runtimeobject.lib")

extern "C" __declspec(dllexport)
void show_toast(const wchar_t* title, const wchar_t* header, const wchar_t* message) {
    RoInitializeWrapper initialize(RO_INIT_MULTITHREADED);
    if (FAILED(initialize)) return;

    ComPtr<IToastNotificationManagerStatics> toastStatics;
    HStringReference classId(RuntimeClass_Windows_UI_Notifications_ToastNotificationManager);
    HRESULT hr = Windows::Foundation::GetActivationFactory(classId.Get(), &toastStatics);
    if (FAILED(hr)) return;

    ComPtr<IXmlDocument> toastXml;
    toastStatics->GetTemplateContent(ToastTemplateType_ToastText02, &toastXml);

    ComPtr<IXmlNodeList> nodeList;
    toastXml->GetElementsByTagName(HStringReference(L"text").Get(), &nodeList);

    // Title node
    ComPtr<IXmlNode> dummy;
    ComPtr<IXmlNode> titleNode;
    nodeList->Item(0, &titleNode);
    ComPtr<IXmlText> titleText;
    toastXml->CreateTextNode(HStringReference(title).Get(), &titleText);
    ComPtr<IXmlNode> titleTextNode;
    titleText.As(&titleTextNode);
    titleNode->AppendChild(titleTextNode.Get(), &dummy);

    // Message node
    ComPtr<IXmlNode> msgNode;
    nodeList->Item(1, &msgNode);
    ComPtr<IXmlText> msgText;
    toastXml->CreateTextNode(HStringReference(message).Get(), &msgText);
    ComPtr<IXmlNode> msgTextNode;
    msgText.As(&msgTextNode);
    msgNode->AppendChild(msgTextNode.Get(), &dummy);

    ComPtr<IToastNotificationFactory> factory;
    ComPtr<IToastNotification> toast;
    Windows::Foundation::GetActivationFactory(
        HStringReference(RuntimeClass_Windows_UI_Notifications_ToastNotification).Get(),
        &factory);
    factory->CreateToastNotification(toastXml.Get(), &toast);

    ComPtr<IToastNotifier> notifier;
    toastStatics->CreateToastNotifierWithId(HStringReference(header).Get(), &notifier);
    notifier->Show(toast.Get());
}
