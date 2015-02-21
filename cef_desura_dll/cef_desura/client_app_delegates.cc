// Copyright (c) 2012 The Chromium Embedded Framework Authors. All rights
// reserved. Use of this source code is governed by a BSD-style license that
// can be found in the LICENSE file.

#include "client_app.h"
#include "client_renderer.h"


namespace client {

// static
void ClientApp::CreateBrowserDelegates(BrowserDelegateSet& delegates) {
}

void JSExtenderCreateRenderDelegates( client::ClientApp::RenderDelegateSet& delegates );


// static
void ClientApp::CreateRenderDelegates(RenderDelegateSet& delegates) {
	JSExtenderCreateRenderDelegates( delegates );
}

// static
void ClientApp::RegisterCustomSchemes(
    CefRefPtr<CefSchemeRegistrar> registrar,
    std::vector<CefString>& cookiable_schemes) {
}

}  // namespace client
