/*******************************************************************************
 * Copyright (c) 2013, Esoteric Software
 * All rights reserved.
 * 
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 * 
 * 1. Redistributions of source code must retain the above copyright notice, this
 *    list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright notice,
 *    this list of conditions and the following disclaimer in the documentation
 *    and/or other materials provided with the distribution.
 * 
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE LIABLE FOR
 * ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 * LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
 * ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 ******************************************************************************/

#include <iostream>
#include <SFML/System/Vector2.hpp>
#include <spine-sfml/RegionAttachment.h>
#include <spine-sfml/Atlas.h>
#include <spine-sfml/Skeleton.h>
#include <spine/Bone.h>
#include <spine/Slot.h>

namespace spine {

RegionAttachment::RegionAttachment (AtlasRegion *region) {
	texture = region->page->texture;
	int u = region->x;
	int u2 = u + region->width;
	int v = region->y;
	int v2 = v + region->height;
	if (region->rotate) {
		vertices[1].texCoords.x = u;
		vertices[1].texCoords.y = v2;
		vertices[2].texCoords.x = u;
		vertices[2].texCoords.y = v;
		vertices[3].texCoords.x = u2;
		vertices[3].texCoords.y = v;
		vertices[0].texCoords.x = u2;
		vertices[0].texCoords.y = v2;
	} else {
		vertices[0].texCoords.x = u;
		vertices[0].texCoords.y = v2;
		vertices[1].texCoords.x = u;
		vertices[1].texCoords.y = v;
		vertices[2].texCoords.x = u2;
		vertices[2].texCoords.y = v;
		vertices[3].texCoords.x = u2;
		vertices[3].texCoords.y = v2;
	}
}

void RegionAttachment::draw (Slot *slot) {
	Skeleton* skeleton = (Skeleton*)slot->skeleton;

	sf::Uint8 r = skeleton->r * slot->r * 255;
	sf::Uint8 g = skeleton->g * slot->g * 255;
	sf::Uint8 b = skeleton->b * slot->b * 255;
	sf::Uint8 a = skeleton->a * slot->a * 255;
	vertices[0].color.r = r;
	vertices[0].color.g = g;
	vertices[0].color.b = b;
	vertices[0].color.a = a;
	vertices[1].color.r = r;
	vertices[1].color.g = g;
	vertices[1].color.b = b;
	vertices[1].color.a = a;
	vertices[2].color.r = r;
	vertices[2].color.g = g;
	vertices[2].color.b = b;
	vertices[2].color.a = a;
	vertices[3].color.r = r;
	vertices[3].color.g = g;
	vertices[3].color.b = b;
	vertices[3].color.a = a;

	updateWorldVertices(slot->bone);

	// SMFL doesn't handle batching for us, so we'll just force a single texture per skeleton.
	skeleton->texture = texture;
	skeleton->vertexArray.append(vertices[0]);
	skeleton->vertexArray.append(vertices[1]);
	skeleton->vertexArray.append(vertices[2]);
	skeleton->vertexArray.append(vertices[3]);
}

void RegionAttachment::updateWorldVertices (spine::Bone *bone) {
	vertices[0].position.x = offset[0] * bone->m00 + offset[1] * bone->m01 + bone->worldX;
	vertices[0].position.y = offset[0] * bone->m10 + offset[1] * bone->m11 + bone->worldY;
	vertices[1].position.x = offset[2] * bone->m00 + offset[3] * bone->m01 + bone->worldX;
	vertices[1].position.y = offset[2] * bone->m10 + offset[3] * bone->m11 + bone->worldY;
	vertices[2].position.x = offset[4] * bone->m00 + offset[5] * bone->m01 + bone->worldX;
	vertices[2].position.y = offset[4] * bone->m10 + offset[5] * bone->m11 + bone->worldY;
	vertices[3].position.x = offset[6] * bone->m00 + offset[7] * bone->m01 + bone->worldX;
	vertices[3].position.y = offset[6] * bone->m10 + offset[7] * bone->m11 + bone->worldY;
}

} /* namespace spine */
