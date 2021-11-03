#
# RadioWare Receiver
# Copyright (C) 2020 - 2021  Luca Cireddu (sardylan@gmail.com)
#
# This program is free software: you can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation, either version 3 of the License.
#
# This program is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.
#
# You should have received a copy of the GNU General Public License
# along with this program.  If not, see <https://www.gnu.org/licenses/>.
#


import asyncio
import json

from fastapi import FastAPI, Request, Response
from hypercorn.asyncio import serve
from hypercorn.config import Config

app: FastAPI = FastAPI()


@app.get("/api/public/v1/test")
async def test_get(request: Request):
    response_body: dict = {
        "test": "test"
    }

    response: Response = Response()
    response.status_code = 200
    response.body = json.dumps(response_body).encode()

    return response


@app.post("/api/public/v1/test")
async def test_post(request: Request):
    request_body: dict = await request.json()

    response_body: dict = dict(request_body)

    response: Response = Response()
    response.status_code = 200
    response.body = json.dumps(response_body).encode()

    return response


if __name__ == "__main__":
    asyncio.run(serve(app, Config()))
