/*
 * Copyright (c) 2023, Andreas Kling <andreas@ladybird.org>
 * Copyright (c) 2023, MacDue <macdue@dueutil.tech>
 *
 * SPDX-License-Identifier: BSD-2-Clause
 */

#include <LibWeb/Bindings/SVGMaskElementPrototype.h>
#include <LibWeb/DOM/Document.h>
#include <LibWeb/SVG/AttributeNames.h>
#include <LibWeb/SVG/SVGMaskElement.h>

namespace Web::SVG {

GC_DEFINE_ALLOCATOR(SVGMaskElement);

SVGMaskElement::SVGMaskElement(DOM::Document& document, DOM::QualifiedName tag_name)
    : SVGGraphicsElement(document, move(tag_name))
{
}

SVGMaskElement::~SVGMaskElement() = default;

void SVGMaskElement::initialize(JS::Realm& realm)
{
    WEB_SET_PROTOTYPE_FOR_INTERFACE(SVGMaskElement);
    Base::initialize(realm);
}

GC::Ptr<Layout::Node> SVGMaskElement::create_layout_node(GC::Ref<CSS::ComputedProperties>)
{
    // Masks are handled as a special case in the TreeBuilder.
    return nullptr;
}

void SVGMaskElement::attribute_changed(FlyString const& name, Optional<String> const& old_value, Optional<String> const& value, Optional<FlyString> const& namespace_)
{
    Base::attribute_changed(name, old_value, value, namespace_);

    if (name == AttributeNames::maskUnits) {
        m_mask_units = AttributeParser::parse_units(value.value_or(String {}));
    } else if (name == AttributeNames::maskContentUnits) {
        m_mask_content_units = AttributeParser::parse_units(value.value_or(String {}));
    }
}

MaskContentUnits SVGMaskElement::mask_content_units() const
{
    return m_mask_content_units.value_or(MaskContentUnits::UserSpaceOnUse);
}

MaskUnits SVGMaskElement::mask_units() const
{
    return m_mask_units.value_or(MaskUnits::ObjectBoundingBox);
}

CSSPixelRect SVGMaskElement::resolve_masking_area(CSSPixelRect const& mask_target) const
{
    // TODO: Resolve this based on the x, y, width, and height of the mask.
    return mask_target.inflated(mask_target.size().scaled(CSSPixels(2) / 10));
}

}
