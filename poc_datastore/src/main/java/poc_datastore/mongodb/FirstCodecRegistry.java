/**
    Copyright (c) 2018 Gabriel Dimitriu All rights reserved.
	DO NOT ALTER OR REMOVE COPYRIGHT NOTICES OR THIS FILE HEADER.

    This file is part of poc_datastore project.

    poc_datanucleus is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    poc_datanucleus is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with poc_datastore.  If not, see <http://www.gnu.org/licenses/>.
 */
package poc_datastore.mongodb;

import org.bson.codecs.Codec;
import org.bson.codecs.configuration.CodecRegistry;

import poc_datastore.pocelement.PocElement;

/**
 * @author Gabriel Dimitriu
 *
 */
public class FirstCodecRegistry implements CodecRegistry {

	private FirstJsonConverter<PocElement> pocConverter = new FirstJsonConverter<>(PocElement.class);
	/**
	 * 
	 */
	public FirstCodecRegistry() {
		// TODO Auto-generated constructor stub
	}

	@SuppressWarnings("unchecked")
	@Override
	public <T> Codec<T> get(Class<T> arg0) {
		if (pocConverter.getEncoderClass().equals(arg0)) {
			return (Codec<T>) pocConverter;
		}
		return null;
	}

}
